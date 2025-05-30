#ifndef ACTUATORS_LED_H
#define ACTUATORS_LED_H

class LED {
public:
    virtual ~LED() = default;
    /**
     * @brief Board specific implementation of GPIO initialization
     */
    virtual void LED_init() = 0;
    /**
     * @brief Board specific implementation of GPIO high output
     */
    virtual void LED_on() = 0;
    /**
     * @brief Board specific implementation of GPIO low output
     */
    virtual void LED_off() = 0;
    /**
     * @brief Board specific implementation of GPIO toggle
     */
    virtual void LED_toggle() = 0;

    /**
     * @brief write high or low to an LED
     * @param value 1 or 0
     */
    virtual void LED_write(int value) = 0;

private:
    /** GPIO number to whom the LED is connected     */
    int _pin = {};
};

#endif
