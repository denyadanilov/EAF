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

class digital_pin {
public:
  digital_pin(uint8_t pin_index, pin_mode mode = pin_mode::NONE);
  digital_pin(const digital_pin &) = delete;
  digital_pin &operator=(const digital_pin &) = delete;
  digital_pin(digital_pin &&) = delete;
  digital_pin &operator=(digital_pin &&) = delete;
  void set_high();
  void set_low();
  pin_state get_state();

private:
  uint8_t pin_index;
};

digital_pin get_pin(uint8_t pin_index, pin_mode mode);
} // namespace eaf