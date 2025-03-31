#include "led.h"
#include "bsp.h"
#include "mbed.h"

#include <cstdint>

namespace BSP{
    void init() {
        init_actuators();
    }

    void init_actuators() {
        get_default_onboard_led()->LED_init();
    }

    void onboard_led_on() {
        get_default_onboard_led()->LED_on();
    }

    void onboard_led_off() {
        get_default_onboard_led()->LED_off();
    }

    void delay(const unsigned int ms) {
        ThisThread::sleep_for(std::chrono::milliseconds(ms));
    }


    LED* get_default_onboard_led() {
        static LED led(23);
        return &led;
    }

};
