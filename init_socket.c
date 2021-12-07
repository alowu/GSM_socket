#include "init_socket.h"

extern uint8_t data[256];

void delay(uint16_t time)
{
  while (time != 0)
  {
    time--;
  }
}

void init_GPIO(void)
{
  // Init LED pins
  GPIO_Init(GPIOE, GPIO_PIN_2, GPIO_MODE_OUT_PP_LOW_SLOW);
  GPIO_Init(GPIOE, GPIO_PIN_3, GPIO_MODE_OUT_PP_LOW_SLOW);
  GPIO_Init(GPIOG, GPIO_PIN_0, GPIO_MODE_OUT_PP_LOW_SLOW);
  GPIO_Init(GPIOG, GPIO_PIN_1, GPIO_MODE_OUT_PP_LOW_SLOW);
  
  // Init M66 POWERKEY pin
  GPIO_Init(GPIOE, GPIO_PIN_1, GPIO_MODE_OUT_PP_LOW_SLOW);
  
  // Init RELE pin
  GPIO_Init(GPIOC, GPIO_PIN_6, GPIO_MODE_OUT_PP_LOW_SLOW);
  
  GPIO_WriteHigh(GPIOE, GPIO_PIN_2);
  GPIO_WriteHigh(GPIOE, GPIO_PIN_3);
  GPIO_WriteHigh(GPIOG, GPIO_PIN_0);
  GPIO_WriteHigh(GPIOG, GPIO_PIN_1);
  
  GPIO_Init(GPIOD, GPIO_PIN_0, GPIO_MODE_OUT_PP_LOW_SLOW);
  GPIO_WriteHigh(GPIOD, GPIO_PIN_0);
}

void turn_on_M66(void)
{
  GPIO_WriteHigh(GPIOE, GPIO_PIN_1);
  delay(10000);
  GPIO_WriteLow(GPIOE, GPIO_PIN_1);
}

uint8_t check_M66(void)
{
  tx_command(AT);
  return check_answer(AT, data);
}

uint8_t init_state_machine(void)
{
  init_GPIO();
  //init_UART2();
  //turn_on_M66();
  return check_M66();
}