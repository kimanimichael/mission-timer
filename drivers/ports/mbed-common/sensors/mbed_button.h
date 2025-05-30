#ifndef MBED_BUTTON_H
#define MBED_BUTTON_H

#include "button.h"
#include "mbed.h"

class MbedButton : public Button {
public:
    explicit MbedButton(int pin);

    void _button_init() override;

    int _button_read() override;

private:
    DigitalInOut _pin;
};

#endif //MBED_BUTTON_H
