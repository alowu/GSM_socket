#include "stm8s.h"
#include "iostm8s105c6.h"

#include "init_socket.h"
#include "tim4_millis.h"

extern uint8_t data[26];
uint8_t str[7] = "Hello\r";

uint8_t result[1];

int main( void )
{
  CLK_DeInit();
  init_TIM4();
  /*if (init_state_machine() == 0)
  {
    //SOFTWARE_RESET;
    GPIO_WriteHigh(GPIOG, GPIO_PIN_0);
    //tx_data("HELLO\r\n", 7);
  }*/
  init_GPIO();
  init_UART2();
  turn_on_M66();
  
  while (1)
  {
    rx_data(2);
    result[0] = memcmp("1", data, 5);
    if (result[0] == 0){
      GPIO_WriteReverse(GPIOG, GPIO_PIN_1);
    }
    else {
      tx_data("ERROR\r",6);
    }
    
    /*if (0 == check_M66())
    {
      GPIO_WriteReverse(GPIOG, GPIO_PIN_1);
    }
    else 
    {
      GPIO_WriteReverse(GPIOG, GPIO_PIN_0);
      delay(1000);
    }  */  
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