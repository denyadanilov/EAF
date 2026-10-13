#pragma once

#include <cstdint>

namespace eaf {

enum class voltage_state {
  RISING_STATE,
  FALLING_STATE,
  CHANGE_STATE,
  ONLOW_STATE,
  ONHIGH_STATE
};

void attach_interrupt(uint8_t pin_index, void (*isr)(), voltage_state state);

} // namespace eaf