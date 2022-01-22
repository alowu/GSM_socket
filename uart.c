#include "uart.h"
#include "command_parser.h"

uint8_t r_data[128];
uint8_t t_data[26];

uint8_t rx_buffer_position;
uint8_t rx_buffer_size;
uint8_t rx_buffer[26];

uint8_t tx_buffer_position;
uint8_t tx_buffer_size;
uint8_t tx_buffer[26];

uint8_t rx_bit = 0;
uint8_t rx_buf[128];

volatile uint8_t counter = 0;
extern uint8_t answer_copied;

INTERRUPT_HANDLER(UART2_TX_IRQHandler, 20)
{
  if (tx_buffer_position < tx_buffer_size)
  {
    UART2_SendData8(tx_buffer[tx_buffer_position++]);
    while(!UART2_SR_TXE)
    {
    }
    counter++;
  }
  else
  {
    tx_buffer_position = 0;
    counter = 0;
    UART2_ITConfig(UART2_IT_TXE, DISABLE);
  }
}
uint8_t amount = 0;
INTERRUPT_HANDLER(UART2_RX_IRQHandler, 21)
{
  uint8_t uart_data;
  if (UART2->SR & UART2_SR_RXNE)
  {
   uart_data = UART2_ReceiveData8();
   rx_buf[rx_bit] = uart_data;//UART2_ReceiveData8();
   rx_bit++;

   if (uart_data == '\r')
   {
      strcpy((char*)r_data, (char*)rx_buf);
      answer_copied = 0;
      char *clip = strstr((char*)r_data, "+CLIP");
      if (clip)
      {
        check_number();
      }
   }
   else if (uart_data == '\n')
   {
     memset(rx_buf, 0, sizeof(rx_buf));
     /* uncommit for echo */
     //tx_data(r_data, rx_bit);         
     rx_bit = 0;
   }
  }
}


void rx_data(uint8_t size)
{
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