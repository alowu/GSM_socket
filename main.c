#include "stm8s.h"
//#include "stm8s_uart2.h"
#include "iostm8s105c6.h"
//#include <stdbool.h>

#include "command_parser.h"
//#include "uart.h"

uint8_t data[256];
                      
uint8_t buffer_position;
uint8_t buffer_size;
uint8_t buffer[256];

volatile uint8_t counter = 0;

uint8_t bytes = 10;

int main( void )
{
  UART2_init();
  enableInterrupts();
  
  while (1)
  {
    //start_comand_servise();
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