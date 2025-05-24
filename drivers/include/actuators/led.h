#ifndef ACTUATORS_LED_H
#define ACTUATORS_LED_H

class LED {
public:
    /**
     *
     * @param pin GPIO attached to pin
     */
    explicit LED(int pin);
    /**
     * @brief Board specific implementation of GPIO initialization
     */
    void LED_init() const;
    /**
     * @brief Board specific implementation of GPIO high output
     */
    void LED_on() const;
    /**
     * @brief Board specific implementation of GPIO low output
     */
    void LED_off() const;

private:
    /** GPIO number to whom the LED is connected     */
    int _pin;
};

#endif
