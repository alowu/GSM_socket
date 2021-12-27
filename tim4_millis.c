#include "tim4_millis.h"

__IO uint32_t current_millis = 0;

void init_TIM4(void)
{
  CLK_HSIPrescalerConfig(CLK_PRESCALER_HSIDIV1); //f_master = HSI = 16Mhz

  /* TIM4 configuration:
  - TIM4CLK is set to 16 MHz, the TIM4 Prescaler is equal to 128 so the TIM1 counter
    clock used is 16 MHz / 128 = 125 000 Hz
  - With 125 000 Hz we can generate time base:
    max time base is 2.048 ms if TIM4_PERIOD = 255 --> (255 + 1) / 125000 = 2.048 ms
    min time base is 0.016 ms if TIM4_PERIOD = 1   --> (  1 + 1) / 125000 = 0.016 ms
  - In this example we need to generate a time base equal to 1 ms
  so TIM4_PERIOD = (0.001 * 125000 - 1) = 124 */

  /* Time base configuration */
  TIM4_TimeBaseInit(TIM4_PRESCALER_128, TIM4_PERIOD);
  
  /* Clear TIM4 update flag */
  TIM4_ClearFlag(TIM4_FLAG_UPDATE);
  
  /* Enable update interrupt */
  TIM4_ITConfig(TIM4_IT_UPDATE, ENABLE);
  
  /* enable interrupts */
  enableInterrupts();
  
  /* Enable TIM4 */
  TIM4_Cmd(ENABLE);
}

uint32_t millis(void)
{
  return current_millis;
}

uint32_t last_t = 0;

void delay(uint32_t time)
{
  while (1)
  {
    uint32_t current = millis();
    if (current - last_t >= time)
    {
      last_t = current;
      break;
    }
  }
}

INTERRUPT_HANDLER(TIM4_UPD_OVF_IRQHandler, 23) 
{   
  current_millis++;
  TIM4_ClearITPendingBit(TIM4_IT_UPDATE);
}