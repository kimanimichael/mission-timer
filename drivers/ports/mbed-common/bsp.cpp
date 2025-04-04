#include "led.h"
#include "bsp.h"
#include "mbed.h"

#include <cstdint>

namespace BSP{
    void BSP_init() {
        BSP_init_actuators();
    }

    void BSP_init_actuators() {
        get_default_onboard_led()->LED_init();
        get_alternate_onboard_led()->LED_init();
    }

    void BSP_LED_on() {
        get_default_onboard_led()->LED_on();
    }

    void BSP_LED_off() {
        get_default_onboard_led()->LED_off();
    }

    void BSP_alternate_LED_on() {
        get_alternate_onboard_led()->LED_on();
    }

    void BSP_alternate_LED_off() {
        get_alternate_onboard_led()->LED_off();
    }

    void BSP_delay(const unsigned int ms) {
        ThisThread::sleep_for(std::chrono::milliseconds(ms));
    }


    LED* get_default_onboard_led() {
        static LED led(23);
        return &led;
    }

    LED* get_alternate_onboard_led() {
        static LED led(30);
        return &led;
    }

};
