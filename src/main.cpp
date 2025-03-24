#include "bsp.h"
#include "timebomb.h"
#include "freertos/FreeRTOS.h"

#define TIMER_PERIOD_MS 1000

static TimeBomb        timeBomb;
static constexpr Event button_pressed_evt = {BUTTON_PRESSED_SIG};

#ifdef ESP32
extern "C" void app_main(void)
#else
int main()
#endif
{
    BSP::BSP_init();
    BSP::BSP_LED_on();
    #ifdef ESP32
    timeBomb._start();
    xTaskCreate(TimeBomb::event_loop, "TimeBomb task", 2048, &timeBomb, 1, nullptr);


    timeBomb._post(&button_pressed_evt);

    if (TimerHandle_t my_timer = xTimerCreate("MyTimer", pdMS_TO_TICKS(TIMER_PERIOD_MS), pdTRUE, nullptr, TimeEvent::tick); my_timer != nullptr) {
        xTimerStart(my_timer, 0);
    }
    #else
    #endif

}
