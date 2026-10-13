#pragma once

#include <cstdint>

namespace eaf {

enum class result { SUCCESS, FAILURE };

struct task_context {
  void (*task_function)(void *) = nullptr;
  void *parameters = nullptr;
};

result schedule_task(task_context *context, const char *task_name,
                     uint32_t stack_depth, uint8_t priority);

} // namespace eaf