#ifndef ESP32_BSP_H
#define ESP32_BSP_H
#include "bsp.h"
#include "freertos/FreeRTOS.h"


namespace ESP_BSP
{
    void ESP32_BSP_Button_init(void);

    void BSP_button_read(TimerHandle_t xTimer);
}
#endif //ESP32_BSP_H
