#include "uart.h"

extern uint8_t data[256];

extern uint8_t buffer_position;
extern uint8_t buffer_size;
extern uint8_t buffer[256];

extern uint8_t counter;

INTERRUPT_HANDLER(UART2_TX_IRQHandler, 20)
 {
    
    UART2_SendData8(buffer[buffer_position++]);
    while(!UART2_SR_TXE)
    {
    }
    counter++;
   
  if (buffer_position == buffer_size)
  {
    buffer_position = 0;
    UART2_ITConfig(UART2_IT_TXE, DISABLE);
  }
 }


 INTERRUPT_HANDLER(UART2_RX_IRQHandler, 21)
 {
    buffer[buffer_position++] = UART2_ReceiveData8();
  
  if (buffer_position == buffer_size || buffer[buffer_position - 1] == '\n')
  {
    memcpy(data, buffer, buffer_size);
    buffer_position = 0;
  } 
 }


void rx_data(uint8_t size)
{
  memcpy(data, '\0', size);
  memcpy(buffer, '\0', size);
  buffer_position = 0;
  buffer_size = size;
}

void tx_data(uint8_t *data, uint8_t size)
{
  memcpy(buffer, data, size);
  buffer_position = 0;
  buffer_size = size;
  
  UART2_ITConfig(UART2_IT_TXE, ENABLE);
}    

void UART2_init(void)
{
  CLK_HSIPrescalerConfig(CLK_PRESCALER_HSIDIV1);
  
  UART2_DeInit();
  /* USART configured as follow:
        - BaudRate = 115200 baud  
        - Word Length = 8 Bits
        - One Stop Bit
        - No parity
        - Receive and transmit enabled
        - UART Clock disabled
  */
  UART2_Init((uint32_t) 115200, UART2_WORDLENGTH_8D,UART2_STOPBITS_1, UART2_PARITY_NO,
                   UART2_SYNCMODE_CLOCK_DISABLE, UART2_MODE_TXRX_ENABLE);
  /* Enable the UART Receive interrupt: this interrupt is generated when the UART
    receive data register is not empty */
  UART2_ITConfig(UART2_IT_RXNE_OR, ENABLE);

  /* Enable UART */
  UART2_Cmd(ENABLE);
}