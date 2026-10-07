#ifndef SRC_ADAPTER_INTERRUPT_H
#define SRC_ADAPTER_INTERRUPT_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

enum voltage_state {
  RISING_STATE,
  FALLING_STATE,
  CHANGE_STATE,
  ONLOW_STATE,
  ONHIGH_STATE
};

typedef enum voltage_state voltage_state_t;

void attach_interrupt(uint8_t pin_index, void (*isr)(), voltage_state_t state);

#ifdef __cplusplus
}
#endif

#endif // SRC_ADAPTER_INTERRUPT_H