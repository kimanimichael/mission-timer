#include "ESP32_fsm.h"

#define QUEUE_LENGTH 10

Active::Active(const StateHandler initial): HSM(initial) {
}

void Active::_start(const UBaseType_t priority) {
    _priority = priority;
    _queue = xQueueCreate(QUEUE_LENGTH, sizeof(Event));
    if (_queue == nullptr) {
        printf("Queue creation failed!\n");
    }
}

void Active::_post(Event const * const e) const {
    xQueueSend(_queue, e, portMAX_DELAY);
}

[[noreturn]] void Active::_event_loop() {
    Event e = {};

    HSM::_init((Event*)nullptr);

    while (true) {
        if (xQueueReceive(_queue, &e, portMAX_DELAY)) {
            HSM::_dispatch(&e);
        }
    }
}
