#include "adapter/pin.hpp"
#include "driver/gpio.h"

namespace eaf {
static uint32_t pin_state_to_esp(pin_state state);
static gpio_mode_t pin_mode_to_esp(pin_mode pin_mode);
static gpio_pull_mode_t pull_mode_to_esp(pin_mode pin_mode);

pin get_pin(uint8_t pin_index, pin_mode mode) {
  return pin(pin_index, mode);
}

pin::pin(uint8_t pin_index, pin_mode mode) : pin_index(pin_index) {
  auto pin_num = static_cast<gpio_num_t>(pin_index);

  gpio_reset_pin(pin_num);
  gpio_set_direction(pin_num, pin_mode_to_esp(mode));
  gpio_set_pull_mode(pin_num, pull_mode_to_esp(mode));
}

void pin::set_high() {
  uint32_t state = pin_state_to_esp(pin_state::HIGH_STATE);
  auto pin_num = static_cast<gpio_num_t>(pin_index);
  gpio_set_level(pin_num, state);
}

void pin::set_low() {
  uint32_t state = pin_state_to_esp(pin_state::LOW_STATE);
  auto pin_num = static_cast<gpio_num_t>(pin_index);
  gpio_set_level(pin_num, state);
}

pin_state pin::get_state() {
  // Implementation for getting the pin state
  return pin_state::LOW_STATE; // Placeholder implementation
}

static uint32_t pin_state_to_esp(pin_state state) {
  switch (state) {
  case pin_state::HIGH_STATE:
    return 1;
  case pin_state::LOW_STATE:
    return 0;
  default:
    return 0;
  }
}

static gpio_mode_t pin_mode_to_esp(pin_mode pin_mode) {
  switch (pin_mode) {
  case pin_mode::OUTPUT_MODE:
    return GPIO_MODE_OUTPUT;
  case pin_mode::INPUT_PULLUP_MODE:
  case pin_mode::INPUT_PULLDOWN_MODE:
    return GPIO_MODE_INPUT;
  default:
    return GPIO_MODE_INPUT;
  }
}

static gpio_pull_mode_t pull_mode_to_esp(pin_mode pin_mode) {
  switch (pin_mode) {
  case pin_mode::INPUT_PULLUP_MODE:
    return GPIO_PULLUP_ONLY;
  case pin_mode::INPUT_PULLDOWN_MODE:
    return GPIO_PULLDOWN_ONLY;
  default:
    return GPIO_FLOATING;
  }
}
} // namespace eaf