#include "led.h"
#include "bsp.h"
#include "ESP32_bsp.h"
#include "freertos/FreeRTOS.h"

#include <cstdint>
#include "driver/gpio.h"
#include "timebomb.h"

namespace BSP{
    void init() {
        init_actuators();
        init_sensors();
    }

    void init_actuators() {
        get_default_onboard_led()->LED_init();
        get_blue_led()->LED_init();
        get_red_led()->LED_init();
        get_green_led()->LED_init();
    }

    void init_sensors() {
        gpio_set_direction(GPIO_NUM_25, GPIO_MODE_INPUT);
        gpio_set_pull_mode(GPIO_NUM_25, GPIO_PULLDOWN_ONLY);

        gpio_set_direction(GPIO_NUM_26, GPIO_MODE_INPUT);
        gpio_set_pull_mode(GPIO_NUM_26, GPIO_PULLDOWN_ONLY);
    }


    void onboard_led_on() {
        get_default_onboard_led()->LED_on();
    }

    void onboard_led_off() {
        get_default_onboard_led()->LED_off();
    }

    void delay(unsigned int ms) {
        vTaskDelay(ms/portTICK_PERIOD_MS);
    }


    LED* get_default_onboard_led() {
        static LED led(2);
        return &led;
    }

    void blue_led_on() {
        get_blue_led()->LED_on();
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

    void trigger_buttons_read() {
        int button_status[2] = {};

        /* state of button. static to persist between func calls */
        static struct ButtonDebouncing {
            uint16_t depressed;
            uint16_t previous;
        } button = {0U, 0U}, button2 = {0U, 0U};

        button_status[0] = gpio_get_level(GPIO_NUM_25);
        button_status[1] = gpio_get_level(GPIO_NUM_26);

        uint16_t tmp = button.depressed;
        uint16_t tmp2 = button2.depressed;

        button.depressed |= (button.previous && button_status[0]); /* set button 1 depressed */
        button.depressed &= (button.previous || button_status[0]); /* set button 1 released */
        button.previous = button_status[0]; /* update history for the next function call */

        button2.depressed |= (button2.previous && button_status[1]); /* set button 2 depressed */
        button2.depressed &= (button2.previous || button_status[1]); /* set button 2 released */
        button2.previous = button_status[1]; /* update history for the next function call */

        tmp ^= button.depressed;
        tmp2 ^= button2.depressed;

        if (tmp) { /*change of button state has occurred */
            if (button_status[0]) { /* button pressed */
                static const Event button_pressed_event = {BUTTON_PRESSED_SIG};
                TimeBomb::get_default_instance()->_post(&button_pressed_event);
            } else { /* button released */
                static const Event button_released_event = {BUTTON_RELEASED_SIG};
                TimeBomb::get_default_instance()->_post(&button_released_event);
            }
        }

        if (tmp2) { /*change of button 2 state has occurred */
            if (button_status[1]) { /* button 2 pressed */
                static const Event button2_pressed_event = {BUTTON2_PRESSED_SIG};
                TimeBomb::get_default_instance()->_post(&button2_pressed_event);
            } else { /* button 2 released */
                static const Event button2_released_event = {BUTTON2_RELEASED_SIG};
                TimeBomb::get_default_instance()->_post(&button2_released_event);
            }
        }


    }

    LED* get_blue_led() {
        static LED led(16);
        return &led;
    }

    LED* get_green_led() {
        static LED led(17);
        return &led;
    }

    LED* get_red_led() {
        static LED led(5);
        return &led;
    }

};

namespace ESP_BSP
{
    void button_read(TimerHandle_t xTimer) {
        BSP::trigger_buttons_read();
    }
}
