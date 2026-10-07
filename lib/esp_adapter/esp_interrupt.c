#include "driver/gpio.h"
#include "interrupt.h"
#include "esp_log.h"

static const char *TAG = "esp_interrupt";

static gpio_int_type_t voltage_state_to_esp(voltage_state_t state);

void attach_interrupt(uint8_t pin_index, void (*isr)(), voltage_state_t state) {
  if (pin_index >= GPIO_NUM_MAX) {
    ESP_LOGE(TAG, "Invalid GPIO pin_index: %d", pin_index);
    return;
  }

  gpio_int_type_t state_esp = voltage_state_to_esp(state);
  gpio_set_intr_type((gpio_num_t)pin_index, state_esp);

  static bool isr_service_installed = false;
  if (!isr_service_installed) {
    gpio_install_isr_service(0);
    isr_service_installed = true;
  }

  gpio_isr_handler_add((gpio_num_t)pin_index, (gpio_isr_t)isr, NULL);
  gpio_intr_enable((gpio_num_t)pin_index);
}

static gpio_int_type_t voltage_state_to_esp(voltage_state_t state) {
  switch (state) {
  case RISING_STATE:
    return GPIO_INTR_POSEDGE;
  case FALLING_STATE:
    return GPIO_INTR_NEGEDGE;
  case CHANGE_STATE:
    return GPIO_INTR_ANYEDGE;
  case ONLOW_STATE:
    return GPIO_INTR_LOW_LEVEL;
  case ONHIGH_STATE:
    return GPIO_INTR_HIGH_LEVEL;
  default:
    return GPIO_INTR_POSEDGE;
  }
}