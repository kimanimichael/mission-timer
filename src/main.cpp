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

    TimeBomb::get_default_instance()->_priority = 1;
    Active::_run(TimeBomb::get_default_instance());

}
