#include "stm8s.h"
#include "iostm8s105c6.h"

#include "init_socket.h"

uint8_t data[256];
                      
uint8_t rx_buffer_position;
uint8_t rx_buffer_size;
uint8_t rx_buffer[256];

uint8_t tx_buffer_position;
uint8_t tx_buffer_size;
uint8_t tx_buffer[256];

volatile uint8_t counter = 0;

uint8_t bytes = 10;

int main( void )
{
  if (init_state_machine() != 0)
  {
    //SOFTWARE_RESET;
  }
  
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