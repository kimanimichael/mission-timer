//
// Created by mikael on 5/30/25.
//
#ifndef ESP_LED_H
#define ESP_LED_H

#include "led.h"

class ESP_LED: public LED {
public:
    explicit ESP_LED(const int pin);

    void LED_init() override;

    void LED_on() override;

    void LED_off() override;

    void LED_toggle() override;

    void LED_write(int value) override;

private:
    int _pin;
    int _pin_state{};
};

#endif //ESP_LED_H
