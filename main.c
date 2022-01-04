#include "stm8s.h"
#include "iostm8s105c6.h"

#include "init_socket.h"
#include "tim4_millis.h"

#include "uart.h"

extern uint8_t r_data[26];
extern uint8_t counter;

int main( void )
{  
  initialize_peripherals();
  initialize_M66();
  sim();
  GPIO_Init(GPIOC, GPIO_PIN_7, GPIO_MODE_IN_FL_IT);

  EXTI_SetExtIntSensitivity(EXTI_PORT_GPIOC, EXTI_SENSITIVITY_FALL_ONLY);
  rim();
  
  while (1)
  {
    GPIO_WriteReverse(GPIOG, GPIO_PIN_1);
    delay(1000);
  }
}

#ifdef USE_FULL_ASSERT

void assert_failed(uint8_t* file, uint32_t line)
{ 
  while (1)
  {
  }
}
#endif