#pragma once
#include "adapter/analog_pin.hpp"
#include "esp_adc/adc_cali.h"
#include "esp_adc/adc_oneshot.h"
#include "hal/adc_types.h"

namespace eaf {

class esp_analog_pin : public analog_pin {
public:
  esp_analog_pin(adc converter_id, channel channel_id, adc_mode mode);
  ~esp_analog_pin() override;
  int read() override;

private:
  adc_unit_t adc_unit;
  adc_channel_t adc_channel;
  adc_oneshot_unit_handle_t adc_handle = nullptr;
  adc_cali_handle_t adc_cali_chan_handle;
  bool do_calibration_chan;
  int raw_result = 0;
  int calibrated_voltage = 0;
  int result = 0;

  static bool adc_calibration_init(adc_unit_t unit, adc_channel_t channel,
                                   adc_atten_t atten,
                                   adc_cali_handle_t *out_handle);
  static adc_unit_t adc_to_unit(adc converter_id);
  static adc_channel_t channel_to_adc_channel(channel channel_id);
  static void configure_by_mode(adc_unit_t *adc_unit,
                                adc_channel_t *adc_channel, adc_mode mode,
                                adc_oneshot_unit_handle_t *adc_handle);
  static void configure_one_shot(adc_unit_t *adc_unit,
                                 adc_channel_t *adc_channel,
                                 adc_oneshot_unit_handle_t *adc_handle);
};

} // namespace eaf