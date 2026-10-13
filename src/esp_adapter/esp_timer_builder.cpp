#include "esp_timer_builder.hpp"
#include "adapter/timer.hpp"
#include "driver/gptimer.h"

namespace eaf {
timer_builder *timer_builder::with_name(const char *name) {
  name_ = name;
  return this;
}

timer_builder *timer_builder::with_config_in_milliseconds() {
  gptimer_config_t timer_config = {
      .clk_src = GPTIMER_CLK_SRC_DEFAULT,
      .direction = GPTIMER_COUNT_UP,
      .resolution_hz = 1000000,
      .intr_priority = 0,
  };

  timer_config_ = timer_config;
  ticks_per_unit_ = 1000;
  return this;
}

timer_builder *timer_builder::with_config_in_seconds() {
  gptimer_config_t timer_config = {
      .clk_src = GPTIMER_CLK_SRC_DEFAULT,
      .direction = GPTIMER_COUNT_UP,
      .resolution_hz = 1000000,
      .intr_priority = 0,
  };

  timer_config_ = timer_config;
  ticks_per_unit_ = 1000000;
  return this;
}

timer_builder *timer_builder::with_alarm_on(uint32_t alarm_time) {
  gptimer_alarm_config_t alarm_config;
  alarm_config.reload_count = 0;
  alarm_config.alarm_count = (uint64_t)alarm_time * ticks_per_unit_;
  alarm_config.flags.auto_reload_on_alarm = true;

  alarm_config_ = alarm_config;
  return this;
}

timer_builder *timer_builder::with_action(isr_invocation_context *context) {
  invocation_context_ = context;
  return this;
}

esp_timer timer_builder::build() {
  gptimer_handle_t timer_handle;

  ESP_ERROR_CHECK(gptimer_new_timer(&timer_config_, &timer_handle));
  ESP_ERROR_CHECK(gptimer_set_alarm_action(timer_handle, &alarm_config_));

  const gptimer_event_callbacks_t event_callbacks = {.on_alarm =
                                                         timer_builder::invoke};
  ESP_ERROR_CHECK(gptimer_register_event_callbacks(
      timer_handle, &event_callbacks, invocation_context_));

  esp_timer timer_instance(name_);
  timer_instance.timer_ = timer_handle;
  return timer_instance;
}

} // namespace eaf