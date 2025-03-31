#include "led.h"
#include "driver/gpio.h"
#include "cstdio"

LED::LED(const int pin) {
    _pin = pin;
}

void LED::LED_init() const {
    gpio_set_direction(static_cast<gpio_num_t>(_pin), GPIO_MODE_OUTPUT);
    printf("LED init\n");
}


void LED::LED_on() const {
    gpio_set_level(static_cast<gpio_num_t>(_pin), 1);
}

void LED::LED_off() const {
    gpio_set_level(static_cast<gpio_num_t>(_pin), 0);
}
