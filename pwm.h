/*
 * pwm.h
 *
 *  Created on: Oct 10, 2020
 *      Author: sguss
 */

#ifndef INC_PWM_H_
#define INC_PWM_H_

#define TIM1_CH1N_PB        13
#define TIM1_CH1_PA         8
#define TIM1_CH2_PA         9

#define LED1_G_PC           9
#define LED2_B_PC           8

#define PWM_VALUE           20
#define MEANDR_TIMER_TICKS               200
#define DEADTIME_TICKS            20

void start_pwm_2(void);
uint8_t pwm_up(uint16_t pwm_value);
uint8_t pwm_down(uint16_t pwm_value);

#endif /* INC_PWM_H_ */
