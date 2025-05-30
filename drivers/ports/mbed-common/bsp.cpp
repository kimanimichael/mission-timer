#include "led.h"
#include "bsp.h"
#include "mbed_button.h"
#include "mbed_led.h"
#include "timebomb.h"
#include <cstdint>

namespace BSP{
    Thread button_thread;

    void init() {
        init_actuators();
        init_sensors();
        button_thread.start(buttons_ticker_start);
    }

    void init_actuators() {
        get_default_onboard_led()->LED_init();
        get_blue_led()->LED_init();
        get_red_led()->LED_init();
    }

    void init_sensors() {
        get_arming_button()->_button_init();
        get_trigger_button()->_button_init();
    }


    void buttons_ticker_start() {
        while (true) {
            trigger_buttons_read();
            ThisThread::sleep_for(10ms);    // choose your period
        }
    }



    void delay(const unsigned int ms) {
        ThisThread::sleep_for(std::chrono::milliseconds(ms));
    }

    LED* get_default_onboard_led() {
        static MbedLED led(23);
        return &led;
    }

    LED* get_blue_led() {
        static MbedLED led(PB_7);
        return &led;
    }

    LED* get_green_led() {
        static MbedLED led(PB_0);
        return &led;
    }

    LED* get_red_led() {
        static MbedLED led(PB_14);
        return &led;
    }

    void onboard_led_on() {
        get_default_onboard_led()->LED_on();
    }

    void onboard_led_off() {
        get_default_onboard_led()->LED_off();
    }

    void blue_led_on() {
        get_blue_led()->LED_on();
    }

    void blue_led_write(const int value) {
        get_blue_led()->LED_write(value);
    }

    void blue_led_toggle() {
        get_blue_led()->LED_toggle();
    }

    void blue_led_off() {
        get_blue_led()->LED_off();
    }

    void green_led_on() {
        get_green_led()->LED_on();
    }

    void green_led_off() {
        get_green_led()->LED_off();
    }

    void red_led_on() {
        get_red_led()->LED_on();
    }

    void red_led_off() {
        get_red_led()->LED_off();
    }

    void red_led_toggle() {
        get_red_led()->LED_toggle();
    }

    Button* get_arming_button() {
        static MbedButton arming_button(10);
        return &arming_button;
    }

    Button* get_trigger_button() {
        static MbedButton arming_button(PC_13);
        return &arming_button;
    }

    void trigger_buttons_read() {
        uint16_t button_status[2] = {};

        static struct ButtonDebouncing {
            uint16_t depressed;
            uint16_t previous;
        } button = {0U, 1U}, button2 = {0U, 0U};

        uint16_t tmp = button.depressed;
        uint16_t tmp2 = button2.depressed;

        button_status[0] = get_trigger_button()->_button_read();
        button_status[1] = get_arming_button()->_button_read();

        button.depressed |= button.previous && button_status[0]; // set button pressed
        button.depressed &= button.previous || button_status[0]; // set released
        button.previous = button_status[0];

        tmp ^= button.depressed;

        if (tmp) { //change in the button state
            if (button_status[0]) { // button pressed
                static constexpr Event button_pressed_evt = {BUTTON_PRESSED_SIG};
                printf("Button 1 pressed\n");
                TimeBomb::get_default_instance()->_post(&button_pressed_evt);
            } else {
                static constexpr Event button_release_evt = {BUTTON_RELEASED_SIG};
                printf("Button 1 released\n");
                TimeBomb::get_default_instance()->_post(&button_release_evt);
            }
        }

        button2.depressed |= button2.previous && button_status[1]; // set button2 pressed
        button2.depressed &= button2.previous || button_status[1]; // set released

        button2.previous = button_status[1];

        tmp2 ^= button2.depressed;

        if (tmp2) { //change in the button2 state
            if (!button_status[1]) { // button2 pressed
                static Event button2_pressed_evt = {BUTTON2_PRESSED_SIG};
                TimeBomb::get_default_instance()->_post(&button2_pressed_evt);
            } else {
                static Event button2_released_evt = {BUTTON2_RELEASED_SIG};
                TimeBomb::get_default_instance()->_post(&button2_released_evt);
            }
        }

    }
};
