#pragma once

namespace eaf {

enum class timer_state { DISABLED, ENABLED, IDLE, RUNNING };

struct inner_timer_state;

class timer {
public:
  timer(const char *name);
  virtual void enable() = 0;
  virtual void disable() = 0;
  virtual void start() = 0;
  virtual void stop() = 0;
};

} // namespace eaf