#include "time.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

uint32_t get_current_time_in_milliseconds() {
    TickType_t ticks = xTaskGetTickCount();
        
    return pdTICKS_TO_MS(ticks); 
}