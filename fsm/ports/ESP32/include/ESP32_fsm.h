/* ESP32 custom FSM header
 * Created by mikael on 3/18/25.
 */

#ifndef ESP32FSM_H
#define ESP32FSM_H

#include "fsm.h"
#include "freertos/FreeRTOS.h"
#include "freertos/queue.h"
#include "freertos/task.h"
#include "queue"
typedef unsigned char  INT8U;                    /* Unsigned  8 bit quantity                           */

/*---------------------------------------------------------------------------*/
/* Active Object facilities... */

class Active: public HSM {
public:
    explicit Active(StateHandler initial);

    void _start(UBaseType_t priority);

    void _post(Event const * e) const;

    [[noreturn]] void _event_loop();
private:
    UBaseType_t _priority = {};    /* Task priority */
    QueueHandle_t _queue = {};   /* Message queue handle */

    /* active object data added in subclasses of Active */
};

#endif //ESP32FSM_H
