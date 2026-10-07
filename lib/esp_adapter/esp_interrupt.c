#include "driver/gpio.h"
#include "interrupt.h"
#include "esp_log.h"

static const char *TAG = "esp_interrupt";	

void attach_interrupt(uint8_t pin_index, void (*isr)(), voltage_state state) {
  if (pin_index >= GPIO_NUM_MAX) {
    ESP_LOGE(TAG, "Invalid GPIO pin_index: %d", pin_index);
    return;
  }

  auto state_esp = voltage_state_to_esp(state);
  gpio_set_intr_type(static_cast<gpio_num_t>(pin_index), state_esp);

  static bool isr_service_installed = false;
  if (!isr_service_installed) {
    gpio_install_isr_service(0);
    isr_service_installed = true;
  }

  gpio_isr_handler_add(static_cast<gpio_num_t>(pin_index),
                       reinterpret_cast<gpio_isr_t>(isr), nullptr);
  gpio_intr_enable(static_cast<gpio_num_t>(pin_index));
}