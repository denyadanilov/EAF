#include "esp_analog_pin.hpp"
#include "esp_adc/adc_cali.h"
#include "esp_adc/adc_cali_scheme.h"
#include "esp_adc/adc_oneshot.h"
#include "esp_err.h"
#include "esp_log.h"
#include "hal/adc_types.h"

#define MAX_ADC_VALUE 4095
#define MAX_PIN_VOLTAGE 3300
#define TAG "ESP_ANALOG_PIN"

namespace eaf {

esp_analog_pin::esp_analog_pin(adc converter_id, channel channel_id,
                               adc_mode mode) {

  adc_unit = adc_to_unit(converter_id);
  adc_channel = channel_to_adc_channel(channel_id);

  configure_by_mode(&adc_unit, &adc_channel, mode, &adc_handle);

  do_calibration_chan = adc_calibration_init(
      adc_unit, adc_channel, ADC_ATTEN_DB_12, &adc_cali_chan_handle);
}

esp_analog_pin::~esp_analog_pin() {
  if (adc_handle != nullptr) {
    ESP_ERROR_CHECK(adc_oneshot_del_unit(adc_handle));
  }
#if ADC_CALI_SCHEME_CURVE_FITTING_SUPPORTED
  if (do_calibration_chan) {
    ESP_ERROR_CHECK(
        adc_cali_delete_scheme_curve_fitting(adc_cali_chan_handle));
  }
#endif
}

int esp_analog_pin::read() {
  ESP_ERROR_CHECK(adc_oneshot_read(adc_handle, adc_channel, &raw_result));

  if (do_calibration_chan) {
    ESP_ERROR_CHECK(adc_cali_raw_to_voltage(adc_cali_chan_handle, raw_result,
                                            &calibrated_voltage));
    result = static_cast<int>(
        static_cast<int64_t>(calibrated_voltage) * MAX_ADC_VALUE /
        MAX_PIN_VOLTAGE);
  } else {
    result = raw_result;
  }

  return result;
}

adc_unit_t esp_analog_pin::adc_to_unit(adc converter_id) {
  switch (converter_id) {
  case adc::ADC1:
    return ADC_UNIT_1;
  case adc::ADC2:
    return ADC_UNIT_2;
  default:
    return ADC_UNIT_1; // Default to ADC_UNIT_1 if NONE or unknown
  }
}

adc_channel_t
esp_analog_pin::channel_to_adc_channel(channel channel_id) {
  switch (channel_id) {
  case channel::CHANNEL0:
    return ADC_CHANNEL_0;
  case channel::CHANNEL1:
    return ADC_CHANNEL_1;
  case channel::CHANNEL2:
    return ADC_CHANNEL_2;
  case channel::CHANNEL3:
    return ADC_CHANNEL_3;
  case channel::CHANNEL4:
    return ADC_CHANNEL_4;
  case channel::CHANNEL5:
    return ADC_CHANNEL_5;
  case channel::CHANNEL6:
    return ADC_CHANNEL_6;
  case channel::CHANNEL7:
    return ADC_CHANNEL_7;
  case channel::CHANNEL8:
    return ADC_CHANNEL_8;
  case channel::CHANNEL9:
    return ADC_CHANNEL_9;
  default:
    return ADC_CHANNEL_0; // Default to CHANNEL0 if unknown
  }
}

void esp_analog_pin::configure_by_mode(
    adc_unit_t *adc_unit, adc_channel_t *adc_channel, adc_mode mode,
    adc_oneshot_unit_handle_t *adc_handle) {
  switch (mode) {
  case adc_mode::ONE_SHOT:
    configure_one_shot(adc_unit, adc_channel, adc_handle);
    break;
  default:
    break;
  }
}

void
esp_analog_pin::configure_one_shot(adc_unit_t *adc_unit,
                                   adc_channel_t *adc_channel,
                                   adc_oneshot_unit_handle_t *adc_handle) {
  adc_oneshot_unit_init_cfg_t init_config = {
      .unit_id = *adc_unit,
  };
  ESP_ERROR_CHECK(adc_oneshot_new_unit(&init_config, adc_handle));

  adc_oneshot_chan_cfg_t config = {
      .atten = ADC_ATTEN_DB_12,
      .bitwidth = ADC_BITWIDTH_DEFAULT,
  };
  ESP_ERROR_CHECK(
      adc_oneshot_config_channel(*adc_handle, *adc_channel, &config));
}

bool
esp_analog_pin::adc_calibration_init(adc_unit_t unit, adc_channel_t channel,
                                     adc_atten_t atten,
                                     adc_cali_handle_t *out_handle) {
  adc_cali_handle_t handle = NULL;
  esp_err_t ret = ESP_FAIL;
  bool calibrated = false;

#if ADC_CALI_SCHEME_CURVE_FITTING_SUPPORTED
  if (!calibrated) {
    ESP_LOGI(TAG, "calibration scheme version is Curve Fitting");
    adc_cali_curve_fitting_config_t cali_config = {
        .unit_id = unit,
        .chan = channel,
        .atten = atten,
        .bitwidth = ADC_BITWIDTH_DEFAULT,
    };
    ret = adc_cali_create_scheme_curve_fitting(&cali_config, &handle);
    if (ret == ESP_OK) {
      calibrated = true;
    }
  }
#endif

  *out_handle = handle;
  return calibrated;
}
} // namespace eaf