#pragma once

#include <cstdint>

namespace eaf {

enum class adc { NONE, ADC1, ADC2 };
enum class channel {
  CHANNEL0,
  CHANNEL1,
  CHANNEL2,
  CHANNEL3,
  CHANNEL4,
  CHANNEL5,
  CHANNEL6,
  CHANNEL7,
  CHANNEL8,
  CHANNEL9
};
enum class adc_mode { ONE_SHOT, CONTINUOUS };

class analog_pin {
public:
  virtual ~analog_pin() = default;
  virtual int read() = 0;
};
} // namespace eaf