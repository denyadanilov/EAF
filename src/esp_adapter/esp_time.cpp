#include "adapter/time.hpp"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

namespace eaf {

unsigned long get_current_time_in_milliseconds() {
  return xTaskGetTickCount() * portTICK_PERIOD_MS;
}

} // namespace eaf