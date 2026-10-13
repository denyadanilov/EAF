#include "adapter/logger.hpp"
#include "driver/gptimer.h"
#include "esp_timer.hpp"

namespace eaf {

void esp_timer::enable() {
  if (state_ != timer_state::DISABLED) {
    return;
  }

  ESP_ERROR_CHECK(gptimer_enable(timer_));
  state_ = timer_state::ENABLED;
  log_message("Timer %s state: %s \n", "esp_timer", "ENABLED");
}

void esp_timer::disable() {
  if (state_ != timer_state::ENABLED && state_ != timer_state::IDLE) {
    return;
  }

  ESP_ERROR_CHECK(gptimer_disable(timer_));
  state_ = timer_state::DISABLED;
  log_message("Timer %s state: %s \n", "esp_timer", "DISABLED");
}

void esp_timer::start() {
  if (state_ != timer_state::ENABLED && state_ != timer_state::IDLE) {
    return;
  }

  ESP_ERROR_CHECK(gptimer_start(timer_));
  state_ = timer_state::RUNNING;
  log_message("Timer %s state: %s \n", "esp_timer", "RUNNING");
}

void esp_timer::stop() {
  if (state_ != timer_state::RUNNING) {
    return;
  }

  ESP_ERROR_CHECK(gptimer_stop(timer_));
  state_ = timer_state::IDLE;
  log_message("Timer %s state: %s \n", "esp_timer", "IDLE");
}

} // namespace eaf