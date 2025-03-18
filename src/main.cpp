#include "bsp.h"

#ifdef ESP32
extern "C" void app_main(void)
#else
int main()
#endif
{
    BSP::BSP_init();
    BSP::BSP_LED_on();
}