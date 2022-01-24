#include "stm8s.h"
#include "iostm8s105c6.h"

#include "init_socket.h"
#include "tim4_millis.h"

#include "uart.h"

uint8_t number[13] = { 0 }; 

int main( void )
{  
  initialize_peripherals();
  initialize_M66();
  
  disableInterrupts();
  //button
  GPIO_Init(GPIOC, GPIO_PIN_7, GPIO_MODE_IN_FL_IT);
  EXTI_SetExtIntSensitivity(EXTI_PORT_GPIOC, EXTI_SENSITIVITY_FALL_ONLY);
  
  //check RIN state
  GPIO_Init(GPIOE, GPIO_PIN_2, GPIO_MODE_IN_FL_IT);
  EXTI_SetExtIntSensitivity(EXTI_PORT_GPIOE, EXTI_SENSITIVITY_FALL_ONLY);
  enableInterrupts();
  
  delay(1000);
  tx_command(CLIP);
  
  while (1)
  {
    //GPIO_WriteReverse(GPIOG, GPIO_PIN_1);
    //delay(1000);
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