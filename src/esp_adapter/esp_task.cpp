#include "adapter/task.hpp"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

namespace eaf {

void task_wrapper(void *parameter) {
  task_context *context = (task_context *)parameter;
  if (context == nullptr || context->task_function == nullptr) {
    vTaskDelete(NULL);
    return;
  }

  void (*function)(void *) = context->task_function;
  void *function_parameters = context->parameters;

  while (true) {
    function(function_parameters);
    vTaskDelay(1);
  }
}

result schedule_task(task_context *context, const char *task_name,
                     uint32_t stack_depth, uint8_t priority) {

  BaseType_t task_result = xTaskCreate(task_wrapper, task_name, stack_depth,
                                       (void *)context, priority, NULL);

  return task_result == pdPASS ? result::SUCCESS
                               : result::FAILURE; // Placeholder implementation
}

} // namespace eaf