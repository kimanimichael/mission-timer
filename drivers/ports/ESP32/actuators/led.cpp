#include "ESP_led.h"
#include "driver/gpio.h"
#include "cstdio"

ESP_LED::ESP_LED(const int pin) {
    _pin = pin;
}

void ESP_LED::LED_init() {
    gpio_set_direction(static_cast<gpio_num_t>(_pin), GPIO_MODE_OUTPUT);
    printf("LED init\n");
}


void ESP_LED::LED_on() {
    _pin_state = 1;
    gpio_set_level(static_cast<gpio_num_t>(_pin), _pin_state);
}

void ESP_LED::LED_off() {
    _pin_state = 0;
    gpio_set_level(static_cast<gpio_num_t>(_pin), _pin_state);
}

void ESP_LED::LED_write(int value) {
    _pin_state = value;
    gpio_set_level(static_cast<gpio_num_t>(_pin), _pin_state);
}

void ESP_LED::LED_toggle() {
    _pin_state = !_pin_state;
    gpio_set_level(static_cast<gpio_num_t>(_pin), _pin_state);
}
