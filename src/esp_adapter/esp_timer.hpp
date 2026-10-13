#include "adapter/timer.hpp"
#include "driver/gptimer.h"

namespace eaf {
class esp_timer : public timer {
public:
  esp_timer(const char *name) : timer(name) {}
  void enable() override;
  void disable() override;
  void start() override;
  void stop() override;

private:
  friend class timer_builder;
  gptimer_handle_t timer_;
  timer_state state_ = timer_state::DISABLED;
};
} // namespace eaf