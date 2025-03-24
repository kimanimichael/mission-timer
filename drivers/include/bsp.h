#ifndef __BSP_H__
#define __BSP_H__
#include "led.h"
#include "fsm.h"

namespace BSP
{
    void BSP_init();

    void BSP_init_actuators();

    void BSP_LED_on();

    void BSP_LED_off();

    void BSP_alternate_LED_on();

    void BSP_alternate_LED_off();

    void BSP_blue_led_on();

    void BSP_blue_led_off();

    void BSP_green_led_on();

    void BSP_green_led_off();

    void BSP_red_led_on();

    void BSP_red_led_off();

    /**
     * @brief blocking wait in line
     * @param ms no. of milliseconds to wait
     */
    void BSP_delay(unsigned int ms);

    LED* get_default_onboard_led();

    LED* get_alternate_onboard_led();

    LED* get_blue_led();

    LED* get_green_led();

    LED* get_red_led();
};

enum  EventSignals {
    BUTTON_PRESSED_SIG = USER_SIGNAL,
    BUTTON_RELEASED_SIG,
    BUTTON2_PRESSED_SIG,
    BUTTON2_RELEASED_SIG,
    TIMEOUT_SIG,
    /* */
    MAX_SIG
   };

#endif
