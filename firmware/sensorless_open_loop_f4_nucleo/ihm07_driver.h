#ifndef __IHM07_DRIVER_H
#define __IHM07_DRIVER_H

#include "stm32f4xx.h"
#include "ihm07_driver_pins.h"

void ihm07_hall_pins_init(void);
void ihm07_hall_interrupt_init(void);
/* void ihm07_hall_state_change_callback(void) __attribute__ ((weak)) */
void ihm07_hall_interrupt_connection_state(FunctionalState state);
uint8_t ihm07_hall_read(void);

void ihm07_led_red_init(void);
#define ihm07_led_red_on() PORT_LED_RED->ODR |= PIN_LED_RED
#define ihm07_led_red_off() PORT_LED_RED->ODR &= ~PIN_LED_RED
#define ihm07_led_red_toggle() PORT_LED_RED->ODR ^= PIN_LED_RED

#define PWM_MAX_VAL ((uint16_t) 1e3)
void ihm07_pwm_and_pins_init(void);
#define ihm07_pwm_set_ch1(val) TIM1->CCR1 = (val) > PWM_MAX_VAL ? PWM_MAX_VAL : (val)
#define ihm07_pwm_set_ch2(val) TIM1->CCR2 = (val) > PWM_MAX_VAL ? PWM_MAX_VAL : (val)
#define ihm07_pwm_set_ch3(val) TIM1->CCR3 = (val) > PWM_MAX_VAL ? PWM_MAX_VAL : (val)

#endif /* __IHM07_DRIVER_H */
