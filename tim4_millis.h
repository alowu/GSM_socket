#ifndef TIM4_MILLIS_H_
#define TIM4_MILLIS_H_

#include "stm8s.h"
#include "stm8s_it.h"

#define TIM4_PERIOD 124

void init_TIM4(void);
uint32_t millis(void);

void delay(uint32_t time);

#endif