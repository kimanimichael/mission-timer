#include "mbed_led.h"
#include "mbed.h"

MbedLED::MbedLED(const int pin):_pin(static_cast<PinName>(pin)) {

}

void MbedLED::LED_init()  {
    _led_state = 0;
    _pin.write(_led_state);
}


void MbedLED::LED_on(){
    _led_state = 1;
    _pin.write(_led_state);
}

void MbedLED::LED_off() {
    _led_state = 0;
    _pin.write(_led_state);
}

void MbedLED::LED_toggle() {
    _led_state = !_led_state;
    _pin.write(_led_state);
}

void MbedLED::LED_write(const int value) {
    _pin.write(value);
}

