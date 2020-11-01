/*
 * pwm.c
 *
 *  Created on: 10 окт. 2020 г.
 *      Author: sguss
 */
#include "main.h"
#include "stm32f4xx.h"

//#define STM32F401CCU

#define STM32F407VET

#ifdef STM32F407VET
#define TIM1_CH1N_PB        13
#define TIM1_CH1_PA         8
#define TIM1_CH2_PA         9
#define LED1_G_PC           9
#define LED2_B_PC           8
#define APBENABLE RCC->APB2ENR|= RCC_APB2ENR_IOPAEN | RCC_APB2ENR_IOPBEN | RCC_APB2ENR_IOPCEN | RCC_APB2ENR_TIM2EN
#endif

#ifdef STM32F401CCU
#define TIM2_CH1_PA         8
#define TIM2_CH2_PA         9
#define LED1_G_PC           9
#define LED2_B_PC           8
//#define APBENABLE RCC->APB1ENR|= RCC_APB1ENR_IOPAEN | RCC_APB1ENR_IOPBEN | RCC_APB1ENR_IOPCEN | RCC_APB1ENR_TIM2EN
#endif


#define DEADTIME_TICKS      20
#define PWM_VALUE           20
#define PWM_PSC				1
#define MEANDR_TIMER_TICKS  839


#define PP_MODE
//#define COMPL_MODE


void start_pwm_2(){
//*
//	APBENABLE;
//    RCC->APB2ENR|= RCC_APB2ENR_IOPAEN | RCC_APB2ENR_IOPBEN | RCC_APB2ENR_IOPCEN | RCC_APB2ENR_TIM1EN;

#ifdef PP_MODE
    //CH1: PWM mode 2, CH2: PWM mode 1, preload enabled on all channels
	// Разрешаем использовать/загружать регистры CCR1 & CCR2
    TIM1->CCMR1=TIM_CCMR1_OC1PE | TIM_CCMR1_OC2PE;
    // Включаем PWM_mode=2 для 1 канала
    TIM1->CCMR1|=TIM_CCMR1_OC1M_0 | TIM_CCMR1_OC1M_1 | TIM_CCMR1_OC1M_2;
    // Включаем PWM_mode=1 для 2 канала
    TIM1->CCMR1|=TIM_CCMR1_OC2M_1 | TIM_CCMR1_OC2M_2;
    // Делитель частоты таймера
    TIM1->PSC = PWM_PSC;
    // Разрешаем использовать каналы 1 и 2 таймера
    TIM1->CCER=TIM_CCER_CC1E | TIM_CCER_CC2E;
    // Делаем выходы таймера активными
    TIM1->BDTR=TIM_BDTR_MOE;
    // Счетчик регистра захвате/сравнения первого канала
    TIM1->CCR1=MEANDR_TIMER_TICKS;
    //TIM2->CCR1=PWM_VALUE;
    // Счетчик регистра захвате/сравнения второго канала
    //TIM2->CCR2=(MEANDR_TIMER_TICKS-DEADTIME_TICKS)/2;
    TIM1->CCR2=0;
    // Задаем период меандра в тиках счетчика
    TIM1->ARR=MEANDR_TIMER_TICKS;
    // Включаем автоматическую загрузку-перезагрузку таймера
    TIM1->CR1=TIM_CR1_ARPE;
    // устанавливаем флаг прерывания при счете вверх и вниз
    TIM1->CR1|= TIM_CR1_CMS_1 | TIM_CR1_CMS_0;
    // Включаем счетчик, таймер начинает работать
    TIM1->CR1|=TIM_CR1_CEN;
    // Обновляем счетчик: инициализация, выставление в начальное значение
    TIM1->EGR=TIM_EGR_UG;
#endif

#ifdef COMPL_MODE
    //CH1: PWM mode with complementary output & deadtime
    TIM2->CCMR1=TIM_CCMR1_OC1M_2 | TIM_CCMR1_OC1M_1 | TIM_CCMR1_OC1PE;
    //
    TIM2->CCER=TIM_CCER_CC1E | TIM_CCER_CC1NE;
    // Делаем выходы таймера активными
    TIM2->BDTR=TIM_BDTR_MOE;
    TIM2->BDTR|= DEADTIME_TICKS;
    // Делитель частоты таймера
    TIM2->PSC = PWM_PSC;
    //
    TIM2->CCR1=PWM_VALUE;
    // Задаем период меандра в тиках счетчика
    TIM2->ARR=MEANDR_TIMER_TICKS;
    // Включаем автоматическую загрузку-перезагрузку таймера
    TIM2->CR1=TIM_CR1_ARPE;
    // Включаем счетчик, таймер начинает работать
    TIM2->CR1|=TIM_CR1_CEN;
    // Обновляем счетчик: инициализация, выставление в начальное значение
    TIM2->EGR=TIM_EGR_UG;
#endif
//*/
}

// Расчет идет по счетчику в канале, который в моде=1,  здесь это 2 канал
uint8_t pwm_up(uint16_t pwm_value){
	uint8_t add_value = 0;
	add_value = (TIM2->CCR2+pwm_value<=(MEANDR_TIMER_TICKS-DEADTIME_TICKS)/2)?pwm_value:(MEANDR_TIMER_TICKS-DEADTIME_TICKS)/2-TIM2->CCR2;
	TIM2->CCR2 += add_value;
	TIM2->CCR1 -= add_value;
	return (pwm_value==add_value)?1:0;
};
uint8_t pwm_down(uint16_t pwm_value){
	uint8_t add_value = 0;
	add_value = (TIM2->CCR2>pwm_value)?pwm_value:TIM2->CCR2;
	TIM2->CCR1 += add_value;
	TIM2->CCR2 -= add_value;
	return (pwm_value==add_value)?1:0;
};

void pwm_test(void){
	for(int i=0; i<200 && pwm_up(10); i++)
		  HAL_Delay(100);
	for(int i=0; i<200 && pwm_down(10); i++)
		  HAL_Delay(100);
}
