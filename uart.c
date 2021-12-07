#include "uart.h"

extern uint8_t data[256];

extern uint8_t rx_buffer_position;
extern uint8_t rx_buffer_size;
extern uint8_t rx_buffer[256];

extern uint8_t tx_buffer_position;
extern uint8_t tx_buffer_size;
extern uint8_t tx_buffer[256];

extern uint8_t counter;

INTERRUPT_HANDLER(UART2_TX_IRQHandler, 20)
 {
    
    UART2_SendData8(tx_buffer[tx_buffer_position++]);
    while(!UART2_SR_TXE)
    {
    }
    counter++;
   
  if (tx_buffer_position == tx_buffer_size)
  {
    tx_buffer_position = 0;
    UART2_ITConfig(UART2_IT_TXE, DISABLE);
  }
 }


 INTERRUPT_HANDLER(UART2_RX_IRQHandler, 21)
 {
    rx_buffer[rx_buffer_position++] = UART2_ReceiveData8();
  
  if (rx_buffer_position == rx_buffer_size || rx_buffer[rx_buffer_position - 1] == '\n')
  {
    memcpy(data, rx_buffer, rx_buffer_size);
    rx_buffer_position = 0;
  } 
 }


void rx_data(uint8_t size)
{
  memcpy(data, '\0', size);
  memcpy(rx_buffer, '\0', size);
  rx_buffer_position = 0;
  rx_buffer_size = size;
}

void tx_data(uint8_t *data, uint8_t size)
{
  memcpy(tx_buffer, data, size);
  tx_buffer_position = 0;
  tx_buffer_size = size;
  
  UART2_ITConfig(UART2_IT_TXE, ENABLE);
}    

void init_UART2(void)
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
  
  enableInterrupts();
}