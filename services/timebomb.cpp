#include "timebomb.h"
#include "hsm.h"
#include "bsp.h"

enum { blink_time = 2U };

TimeBomb* TimeBomb::instance = nullptr;

TimeBomb::TimeBomb(): Active((TimeBomb::initial_trampoline)) {
    te = TimeEvent::get_default_instance(TIMEOUT_SIG, this);
    instance = this;
}

State TimeBomb::initial_trampoline(Event const* const e) {
    return instance->_initial(e);
}

State TimeBomb::_initial(Event const* const e) {
    return TRAN(wait_for_button_trampoline);
}

State TimeBomb::armed_trampoline(Event const * const e) {
    return instance->_armed(e);
}

State TimeBomb ::_armed(Event const * const e) {
    State status;
    switch (e->_sig) {
        case BUTTON2_PRESSED_SIG: {
                status = TRAN(defused_trampoline);
                break;
        }
        case INIT_SIGNAL: {
                status = TRAN(initial_trampoline);
                break;
        }
        default: {
                status = SUPER(HSM::_top);
                break;
        }
    }
    return status;
}

State TimeBomb::wait_for_button_trampoline(Event const* const e) {
    return instance->_wait_for_button(e);
}

State TimeBomb::_wait_for_button(Event const * const e) {
    State status;
    switch (e->_sig) {

        case ENTRY_SIGNAL: {
                BSP::BSP_blue_led_on();
                status = HANDLED_STATUS;
                break;
        }
        case EXIT_SIGNAL: {
                BSP::BSP_blue_led_off();
                status = HANDLED_STATUS;
                break;
        }
        case BUTTON_PRESSED_SIG: {
                blink_ctr = 3;
                status = TRAN(blink_trampoline);
                break;
        }
        default: {
                status = SUPER(armed_trampoline);
                break;
        }
    }
    return status;
}

State TimeBomb::blink_trampoline(Event const* const e) {
    return instance->_blink(e);
}

State TimeBomb::_blink(Event const * const e) {
    State status;
    switch (e->_sig) {
        case ENTRY_SIGNAL: {
                printf("Enter blink\n");
                BSP::BSP_blue_led_on();
                te->_arm((blink_time), 0U);
                status = HANDLED_STATUS;
                break;
        }
        case EXIT_SIGNAL: {
                printf("Exit blink\n");
                BSP::BSP_blue_led_off();
                status = HANDLED_STATUS;
                break;
        }
        case TIMEOUT_SIG: {
                printf("Timeout in blink\n");
                status = TRAN(pause_trampoline);
                break;
        }
        default: {
                status = SUPER(armed_trampoline);
                break;
        }
    }
    return status;
}

State TimeBomb::pause_trampoline(Event const* const e) {
    return instance->_pause(e);
}

State TimeBomb::_pause(Event const * const e) {
    State status;
    switch (e->_sig) {
        case ENTRY_SIGNAL: {
                printf("Enter pause\n");
                te->_arm((blink_time), 0U);
                status = HANDLED_STATUS;
                break;
        }

        case TIMEOUT_SIG: {
                printf("Timeout in pause\n");
                if (--blink_ctr > 0) {
                    status = TRAN(blink_trampoline);
                } else {
                    status = TRAN(boom_trampoline);
                }
                break;
        }
        default: {
                status = SUPER(armed_trampoline);
                break;
        }
    }
    return status;
}

State TimeBomb::boom_trampoline(Event const* const e) {
    return instance->_boom(e);
}

State TimeBomb::_boom(Event const * const e) {
    State status;
    switch (e->_sig) {

        case ENTRY_SIGNAL: {
                printf("Enter boom\n");
                BSP::BSP_green_led_on();
                BSP::BSP_red_led_on();
                BSP::BSP_blue_led_on();
                status = HANDLED_STATUS;
                break;
        }

        case EXIT_SIGNAL: {
                printf("Exit boom\n");
                BSP::BSP_green_led_off();
                BSP::BSP_red_led_off();
                BSP::BSP_blue_led_off();
                status = HANDLED_STATUS;
                break;
        }
        default: {
                status = SUPER(armed_trampoline);
                break;
        }
    }
    return status;
}

State TimeBomb::defused_trampoline(Event const* const e) {
    return instance->_defused(e);
}

State TimeBomb::_defused(Event const * const e) {
    State status;
    switch (e->_sig) {

        case ENTRY_SIGNAL: {
                BSP::BSP_blue_led_on();
                status = HANDLED_STATUS;
                break;
        }
        case EXIT_SIGNAL: {
                BSP::BSP_blue_led_off();
                status = HANDLED_STATUS;
                break;
        }
        case BUTTON2_PRESSED_SIG: {
                status = TRAN(armed_trampoline);
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




