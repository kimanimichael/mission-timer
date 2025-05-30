#ifndef MBED_LED_H
#define MBED_LED_H

#include "led.h"
#include "mbed.h"

class MbedLED : public LED {
public:
    explicit MbedLED(int pin);
    /**
     * @brief Board specific implementation of GPIO initialization
     */
    void LED_init() override;
    /**
     * @brief Board specific implementation of GPIO high output
     */
    void LED_on() override;
    /**
     * @brief Board specific implementation of GPIO low output
     */
    void LED_off() override;

    /**
     * @brief Board specific implementation of GPIO toggle
     */
     void LED_toggle() override;

    void LED_write(int value) override;
private:
    DigitalOut _pin;
    uint8_t _led_state;
};

#endif //MBED_LED_H
