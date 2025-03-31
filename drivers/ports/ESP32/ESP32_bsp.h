#ifndef ESP32_BSP_H
#define ESP32_BSP_H
#include "freertos/FreeRTOS.h"

namespace ESP_BSP
{
    /**
     * @brief Trampoline for BSP::trigger_buttons_read
     * @param xTimer Handle to the timer that triggered the callback
     */
    void button_read(TimerHandle_t xTimer);
}
#endif //ESP32_BSP_H
