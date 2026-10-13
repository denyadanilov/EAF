#pragma once

#include "driver/gptimer.h"
#include "esp_timer.hpp"
#include <cstdint>

namespace eaf {

class timer;

class timer_builder {
  static bool invoke(gptimer_handle_t timer,
                     const gptimer_alarm_event_data_t *event_data, void *arg) {

    auto *context = static_cast<isr_invocation_context *>(arg);
    if (context && context->callback) {
      context->callback();
      return true;
    }
    return false;
  }

  struct isr_invocation_context {
    void (*callback)() = nullptr;
    void *arg = nullptr;
  };

private:
  void (*callback_)() = nullptr;

public:
  timer_builder *with_name(const char *name);
  timer_builder *with_config_in_milliseconds();
  timer_builder *with_config_in_seconds();
  timer_builder *with_alarm_on(uint32_t alarm_time);
  timer_builder *with_action(isr_invocation_context *context);
  esp_timer build();

private:
  const char *name_;
  gptimer_config_t timer_config_;
  gptimer_alarm_config_t alarm_config_;
  isr_invocation_context *invocation_context_;
  uint64_t ticks_per_unit_;
};

} // namespace eaf