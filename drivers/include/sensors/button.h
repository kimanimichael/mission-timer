#ifndef BUTTON_H
#define BUTTON_H

class Button {
public:
    /**
     * @brief Board specific implementation of GPIO initialization
     */
    virtual void _button_init();
    /**
     * @brief Board specific implementation of GPIO high output
     */
    virtual int _button_read();
private:
    /** GPIO number to whom the LED is connected     */
    int _pin;
};

#endif //BUTTON_H
