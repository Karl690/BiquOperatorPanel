#include "timer_pwm.h"
#include "main.h"
#include "global.h"  // for mcuClocks

typedef struct {
  TIM_TypeDef* tim;
  volatile uint32_t* rcc_src;
  uint8_t rcc_bit;
} TIMER;

static const TIMER pwmTimer[_TIM_CNT] = {
  {TIM1,  &RCC->APB2ENR, 0},   // Timer1  APB2 bit0
  {TIM2,  &RCC->APB1ENR, 0},   // Timer2  APB1 bit0
  {TIM3,  &RCC->APB1ENR, 1},   // Timer3  APB1 bit1
  {TIM4,  &RCC->APB1ENR, 2},   // Timer4  APB1 bit2
  {TIM5,  &RCC->APB1ENR, 3},   // Timer5  APB1 bit3
  {TIM6,  &RCC->APB1ENR, 4},   // Timer6  APB1 bit4
  {TIM7,  &RCC->APB1ENR, 5},   // Timer7  APB1 bit5
  {TIM8,  &RCC->APB2ENR, 1},   // Timer8  APB2 bit1
  {TIM9,  &RCC->APB2ENR, 16},  // Timer9  APB2 bit16
  {TIM10, &RCC->APB2ENR, 17},  // Timer10 APB2 bit17
  {TIM11, &RCC->APB2ENR, 18},  // Timer11 APB2 bit18
  {TIM12, &RCC->APB1ENR, 6},   // Timer12 APB1 bit6
  {TIM13, &RCC->APB1ENR, 7},   // Timer13 APB1 bit7
  {TIM14, &RCC->APB1ENR, 8},   // Timer14 APB1 bit8
};

void TIM_PWM_SetDutyCycle(uint16_t tim_ch, uint8_t duty)
{
  uint16_t timerIndex = TIMER_GET_TIM(tim_ch);
  uint16_t channel = TIMER_GET_CH(tim_ch);
  const TIMER* timer = &pwmTimer[timerIndex];
  switch (channel)
  {
    case 0: timer->tim->CCR1 = duty; break;
    case 1: timer->tim->CCR2 = duty; break;
    case 2: timer->tim->CCR3 = duty; break;
    case 3: timer->tim->CCR4 = duty; break;
  }
}
