#ifndef SERVICES_TIMEBOMB_H
#define SERVICES_TIMEBOMB_H

#include "ESP32_fsm.h"

class TimeBomb: public Active {
public:
    TimeBomb();

    static State initial_trampoline(Event const * const e);

    State _initial(Event const * const e);

    static State armed_trampoline(Event const * const e);

    State _armed(Event const * e);

    static State wait_for_button_trampoline(Event const * const e);

    State _wait_for_button(Event const * e);

    static State blink_trampoline(Event const * const e);

    State _blink(Event const * e);

    static State pause_trampoline(Event const * const e);

    State _pause(Event const * e);

    static State boom_trampoline(Event const * const e);

    State _boom(Event const * e);

    static State defused_trampoline(Event const * const e);

    State _defused(Event const * e);

    static TimeBomb* get_default_instance();

    TimeEvent *te;

    uint32_t blink_ctr = {};
private:
    static TimeBomb* instance;
};

#endif