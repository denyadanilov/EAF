#pragma once

#include <cstdint>

namespace eaf {

enum class pin_mode {
  NONE,
  OUTPUT_MODE,
  INPUT_PULLUP_MODE,
  INPUT_PULLDOWN_MODE,
  INPUT_MODE,
};

enum class pin_state { LOW_STATE, HIGH_STATE };

class pin {
public:
  pin(uint8_t pin_index, pin_mode mode = pin_mode::NONE);
  pin(const pin &) = delete;
  pin &operator=(const pin &) = delete;
  pin(pin &&) = delete;
  pin &operator=(pin &&) = delete;
  void set_high();
  void set_low();
  pin_state get_state();

private:
  uint8_t pin_index;
};

pin get_pin(uint8_t pin_index, pin_mode mode);
} // namespace eaf