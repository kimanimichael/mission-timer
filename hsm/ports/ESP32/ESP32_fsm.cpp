#include "ESP32_fsm.h"
#include "bsp.h"
#include "ESP32_bsp.h"

#define QUEUE_LENGTH 10
#define MAX_TIME_EVENTS 10

#define TIMER_PERIOD_MS 100
#define BUTTON_INTERVAL_MS 10

static constexpr Event button_pressed_evt = {BUTTON_PRESSED_SIG};

static uint64_t param;

void Active::_run(const Active *object) {
    object->_start();
    xTaskCreate(Active::event_loop, "TimeBomb task", 2048, &param, 1, nullptr);


    // object->_post(&button_pressed_evt);

    if (TimerHandle_t my_timer = xTimerCreate("MyTimer", pdMS_TO_TICKS(TIMER_PERIOD_MS), pdTRUE, nullptr, TimeEvent::tick); my_timer != nullptr) {
        xTimerStart(my_timer, 0);
    }

    if (TimerHandle_t button_timer = xTimerCreate("ButtonTimer", pdMS_TO_TICKS(BUTTON_INTERVAL_MS), pdTRUE, nullptr, ESP_BSP::BSP_button_read); button_timer != nullptr) {
        xTimerStart(button_timer, 0);
    }
}


Active * Active::active_instance = nullptr;

Active::Active(const StateHandler initial): HSM(initial) {
    active_instance = this;
    _queue = xQueueCreate(QUEUE_LENGTH, sizeof(Event));
}

void Active::_start() const {
    assert(_queue != nullptr);
    if (_queue == nullptr) {
        printf("Queue creation failed!\n");
    }
}

void Active::_post(Event const * const e) const {
    assert(_queue != nullptr);
    printf("Posting to queue\n");
    xQueueSend(_queue, e, portMAX_DELAY);
}

void Active::event_loop(void* param) {
    active_instance->_event_loop();
}


[[noreturn]] void Active::_event_loop() {
    Event e = {};

    HSM::_init((Event*)nullptr);

    while (true) {
        printf("Waiting for event...\n");
        if (xQueueReceive(_queue, &e, portMAX_DELAY)) {
            printf("Event received...\n");
            HSM::_dispatch(&e);
        }
    }
}

TimeEvent * TimeEvent::time_event_instance = nullptr;

static TimeEvent *l_t_evt[MAX_TIME_EVENTS];
static uint_fast8_t l_t_evt_num = {};

SemaphoreHandle_t TimeEvent::_events_mutex = xSemaphoreCreateMutex();
SemaphoreHandle_t TimeEvent::_parameters_mutex = xSemaphoreCreateMutex();

TimeEvent::TimeEvent(const Signal sig, Active *act) : Event(), _act(act) {
    _sig = sig;
    if (xSemaphoreTake(TimeEvent::_events_mutex, portMAX_DELAY)) {
        l_t_evt[l_t_evt_num] = this;
        l_t_evt_num++;
    }
    xSemaphoreGive(TimeEvent::_events_mutex);
    time_event_instance = this;
}

void TimeEvent::_arm(const uint32_t timeout, const uint32_t interval) {
    if (xSemaphoreTake(TimeEvent::_parameters_mutex, portMAX_DELAY)) {
        _timeout = timeout;
        _interval = interval;
    }
    l_t_evt[0] -> _timeout = timeout;
    _timeout = timeout;
    printf("Armed successfully to %ld \n", _timeout);
    xSemaphoreGive(TimeEvent::_parameters_mutex);
}

void TimeEvent::_disarm() {
    if (xSemaphoreTake(TimeEvent::_parameters_mutex, portMAX_DELAY)) {
        _timeout = 0U;
    }
    xSemaphoreGive(TimeEvent::_parameters_mutex);
}

void TimeEvent::tick(TimerHandle_t xTimer) {
    time_event_instance->_tick();
}


void TimeEvent::_tick() const {
    for (uint_fast8_t i = 0; i < l_t_evt_num; i++) {
        // ESP_ERROR_CHECK(l_t_evt[i] != static_cast<TimeEvent*>(nullptr));
        if (l_t_evt[i] ->_timeout > 0U) {
            l_t_evt[i] ->_timeout --;
            if (l_t_evt[i] ->_timeout == 0U) {
                printf("Timeout reached. Posting\n");
                l_t_evt[i] ->_act->_post(this);
                l_t_evt[i] -> _timeout = l_t_evt[i]->_interval;
            }
        }
    }
}

TimeEvent* TimeEvent::get_default_instance(const Signal sig, Active *act) {
    static TimeEvent te(sig, act);
    return &te;
}


