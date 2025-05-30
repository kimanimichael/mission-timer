#include "mbed_button.h"

MbedButton::MbedButton(int pin): _pin(static_cast<PinName>(pin)) {
    _pin.input();
    _pin.mode(PullDown);
}

void MbedButton::_button_init() {
    _pin.mode(PullDown);
}

int MbedButton::_button_read()  {
    return _pin.read();
}

