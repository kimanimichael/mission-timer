#ifndef BSP_H_
#define BSP_H_
#include <button.h>

#include "led.h"
#include "hsm.h"

namespace BSP
{
    /**
    * @brief Init all board functions
    */
    void init();
    /**
    * @brief Configures actuator GPIOs
    */
    void init_actuators();
    /**
    * @brief Configure sensor GPIOs
    */
    void init_sensors();
    /**
    * @brief Turn onboard LED ON
    * @note Init actuators must have been called
    */
    void onboard_led_on();
    /**
    * @brief Turn onboard LED off
    */
    void onboard_led_off();
    /**
    * @brief Turn blue LED ON
    * @note Init actuators must have been called
    */
    void blue_led_on();
    /**
    * @brief Turn blue LED OFF
    * @note Init actuators must have been called
    */
    void blue_led_off();
    /**
    * @brief Turn green LED ON
    * @note Init actuators must have been called
    */
    void green_led_on();
    /**
    * @brief Turn green LED OFF
    * @note Init actuators must have been called
    */
    void green_led_off();
    /**
    * @brief Turn red LED ON
    * @note Init actuators must have been called
    */
    void red_led_on();
    /**
    * @brief Turn red LED OFF
    * @note Init actuators must have been called
    */
    void red_led_off();
    /**
    * @brief Check status of trigger and defuse buttons
    * @note Init sensors must have been called
    */
    void trigger_buttons_read();
    /**
    * @brief Check status of trigger and defuse buttons
    * @note Init sensors must have been called
    */
    void buttons_ticker_start();
    /**
     * @brief blocking wait in line
     * @param ms no. of milliseconds to wait
     */
    void delay(unsigned int ms);
    /**
    * @brief Get on dev board led default instance
    * @return pointer to onboard LED
    */
    LED* get_default_onboard_led();
    /**
    * @brief Get blue LED default instance
    * @return pointer to blue LED
    */
    LED* get_blue_led();
    /**
    * @brief Get green LED default instance
    * @return pointer to green LED
    */
    LED* get_green_led();
    /**
    * @brief Get red LED  default instance
    * @return pointer to red LED
    */
    LED* get_red_led();
    /**
    * @brief Get arming button  default instance
    * @return pointer to arming button
    */
    Button* get_arming_button();
    /**
    * @brief Get trigger button default instance
    * @return pointer to trigger button
    */
    Button* get_trigger_button();
};

/* Custom event signals. Extends from HSM signals */
enum  EventSignals {
    BUTTON_PRESSED_SIG = USER_SIGNAL,
    BUTTON_RELEASED_SIG,
    BUTTON2_PRESSED_SIG,
    BUTTON2_RELEASED_SIG,
    TIMEOUT_SIG,
    /* */
    MAX_SIG
   };

#endif
