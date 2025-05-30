#ifndef SERVICES_TIMEBOMB_H
#define SERVICES_TIMEBOMB_H


#ifdef ESP32
#include "ESP32_fsm.h"
#else
#include "mbed_hsm.h"
#endif

class TimeBomb: public Active {
public:
    /**
     * @brief Init te and instance
     */
    TimeBomb();

    /**
     * @brief First timebomb state
     * @param e event to be handled
     * @return
     */
    State        _initial(Event const * e);
    /**
     * @brief Armed super state. On INIT transitions to _initial state
     * @param e event to be handled
     * @return
     */
    State _armed(Event const * e);
    /**
     * @brief Wait for trigger button 1 press
     * @param e event to be handled
     * @return
     */
    State _wait_for_button(Event const * e);
    /**
     * @brief Red LED ON for _timeout in te
     * @param e event to be handled
     * @return
     */
    State _blink(Event const * e);
    /**
     * @brief Red LED OFF for _timeout in te
     * @param e event to be handled
     * @return
     */
    State _pause(Event const * e);
    /**
     * @brief Boom. All LEDs ON
     * @param e event to be handled
     * @return
     */
    State _boom(Event const * e);
    /**
     * @brief Defused. Can't be triggered
     * @param e event to be handled
     * @return
     */
    State _defused(Event const * e);
    /**
     * @brief Get default instance for TimeBomb
     * @return Pointer to TimeBomb instance
     */
    static TimeBomb* get_default_instance();
    /** Associated TimeEvent */
    TimeEvent *te;
    /** Number of blinks before detonation */
    uint32_t blink_ctr = {};
private:
    /** Instance used for trampoline functions */ // @todo Find better solution to trampoline functions
};

#endif
