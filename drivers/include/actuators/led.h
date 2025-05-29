#ifndef ACTUATORS_LED_H
#define ACTUATORS_LED_H

class LED {
public:
    /**
     * @brief Board specific implementation of GPIO initialization
     */
    virtual void LED_init();
    /**
     * @brief Board specific implementation of GPIO high output
     */
    virtual void LED_on();
    /**
     * @brief Board specific implementation of GPIO low output
     */
    virtual void LED_off();
    /**
     * @brief Board specific implementation of GPIO toggle
     */
    virtual void LED_toggle();

    /**
     * @brief write high or low to an LED
     * @param value 1 or 0
     */
    virtual void LED_write(int value);

private:
    /** GPIO number to whom the LED is connected     */
    int _pin;
};

#endif
