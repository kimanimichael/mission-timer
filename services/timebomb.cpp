#include "timebomb.h"
#include "hsm.h"
#include "bsp.h"

enum { blink_time = 2U };

TimeBomb* TimeBomb::instance = nullptr;

StateHandler initial = std::bind(&TimeBomb::_initial, TimeBomb::get_default_instance(), std::placeholders::_1);
StateHandler armed = std::bind(&TimeBomb::_armed, TimeBomb::get_default_instance(), std::placeholders::_1);
StateHandler wait_for_button = std::bind(&TimeBomb::_wait_for_button, TimeBomb::get_default_instance(), std::placeholders::_1);
StateHandler blink = std::bind(&TimeBomb::_blink, TimeBomb::get_default_instance(), std::placeholders::_1);
StateHandler pause = std::bind(&TimeBomb::_pause, TimeBomb::get_default_instance(), std::placeholders::_1);
StateHandler boom = std::bind(&TimeBomb::_boom, TimeBomb::get_default_instance(), std::placeholders::_1);
StateHandler defused = std::bind(&TimeBomb::_defused, TimeBomb::get_default_instance(), std::placeholders::_1);


TimeBomb::TimeBomb(): Active((initial)) {
    te = TimeEvent::get_default_instance(TIMEOUT_SIG, this);
    instance = this;
}

State TimeBomb::_initial(Event const* const e) {
    return TRAN(wait_for_button);
}

State TimeBomb ::_armed(Event const * const e) {
    State status;
    switch (e->_sig) {
        case BUTTON2_PRESSED_SIG: {
                status = TRAN(defused);
                break;
        }
        case INIT_SIGNAL: {
                status = TRAN(initial);
                break;
        }
        default: {
                status = SUPER(HSM::_top);
                break;
        }
    }
    return status;
}


State TimeBomb::_wait_for_button(Event const * const e) {
    State status;
    switch (e->_sig) {

        case ENTRY_SIGNAL: {
                BSP::green_led_on();
                status = HANDLED_STATUS;
                break;
        }
        case EXIT_SIGNAL: {
                BSP::green_led_off();
                status = HANDLED_STATUS;
                break;
        }
        case BUTTON_PRESSED_SIG: {
                blink_ctr = 3;
                status = TRAN(blink);
                break;
        }
        default: {
                status = SUPER(armed);
                break;
        }
    }
    return status;
}

State TimeBomb::_blink(Event const * const e) {
    State status;
    switch (e->_sig) {
        case ENTRY_SIGNAL: {
                printf("Enter blink\n");
                BSP::red_led_on();
                te->_arm(blink_time, 0U);
                status = HANDLED_STATUS;
                break;
        }
        case EXIT_SIGNAL: {
                printf("Exit blink\n");
                BSP::red_led_off();
                status = HANDLED_STATUS;
                break;
        }
        case TIMEOUT_SIG: {
                printf("Timeout in blink\n");
                status = TRAN(pause);
                break;
        }
        default: {
                status = SUPER(armed);
                break;
        }
    }
    return status;
}

State TimeBomb::_pause(Event const * const e) {
    State status;
    switch (e->_sig) {
        case ENTRY_SIGNAL: {
                printf("Enter pause\n");
                te->_arm(blink_time, 0U);
                status = HANDLED_STATUS;
                break;
        }

        case TIMEOUT_SIG: {
                printf("Timeout in pause\n");
                if (--blink_ctr > 0) {
                    status = TRAN(blink);
                } else {
                    status = TRAN(boom);
                }
                break;
        }
        default: {
                status = SUPER(armed);
                break;
        }
    }
    return status;
}

State TimeBomb::_boom(Event const * const e) {
    State status;
    switch (e->_sig) {

        case ENTRY_SIGNAL: {
                printf("Enter boom\n");
                BSP::green_led_on();
                BSP::red_led_on();
                BSP::blue_led_on();
                status = HANDLED_STATUS;
                break;
        }

        case EXIT_SIGNAL: {
                printf("Exit boom\n");
                BSP::green_led_off();
                BSP::red_led_off();
                BSP::blue_led_off();
                status = HANDLED_STATUS;
                break;
        }
        default: {
                status = SUPER(armed);
                break;
        }
    }
    return status;
}

State TimeBomb::_defused(Event const * const e) {
    State status;
    switch (e->_sig) {

        case ENTRY_SIGNAL: {
                BSP::blue_led_on();
                status = HANDLED_STATUS;
                break;
        }
        case EXIT_SIGNAL: {
                BSP::blue_led_off();
                status = HANDLED_STATUS;
                break;
        }
        case BUTTON2_PRESSED_SIG: {
                status = TRAN(armed);
                break;
        }
        default: {
                status = SUPER(HSM::_top);
                break;
        }
    }
    return status;
}

TimeBomb* TimeBomb::get_default_instance() {
    static TimeBomb time_bomb;
    return &time_bomb;
}




