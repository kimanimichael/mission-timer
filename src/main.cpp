#ifdef ESP32
#include "ESP32_fsm.h"
#endif

#include "bsp.h"
#include "timebomb.h"

#define TIMER_PERIOD_MS 1000

#ifdef ESP32
extern "C" void app_main(void)
#else
int main()
#endif
{
    BSP::init();

    #ifdef ESP32
    TimeBomb::get_default_instance()->_priority = 1;
    Active::_run(TimeBomb::get_default_instance());
    #else
    #endif

}
