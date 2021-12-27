#include "init_socket.h"
#include "tim4_millis.h"

extern uint8_t data[26];

/*void delay(uint16_t time)
{
  while (time != 0)
  {
    time--;
  }
}*/
/*
с + работает
с - нет
*/

void init_GPIO(void)
{
  GPIO_DeInit(GPIOC);
  GPIO_DeInit(GPIOE);
  GPIO_DeInit(GPIOG);
  // Init LED pins
  //GPIO_Init(GPIOE, GPIO_PIN_2, GPIO_MODE_OUT_PP_LOW_SLOW);
  GPIO_Init(GPIOE, GPIO_PIN_3, GPIO_MODE_OUT_PP_LOW_SLOW);
  GPIO_Init(GPIOG, GPIO_PIN_0, GPIO_MODE_OUT_PP_LOW_SLOW);
  GPIO_Init(GPIOG, GPIO_PIN_1, GPIO_MODE_OUT_PP_LOW_SLOW);
  
  // Init M66 POWERKEY pin
  GPIO_Init(GPIOE, GPIO_PIN_0, GPIO_MODE_OUT_PP_LOW_SLOW);
  
  // Init RELE pin
  GPIO_Init(GPIOC, GPIO_PIN_6, GPIO_MODE_OUT_PP_LOW_SLOW);
}

void test(void)
{
  GPIO_WriteReverse(GPIOG, GPIO_PIN_1);
}

void turn_on_M66(void)
{
  GPIO_WriteHigh(GPIOE, GPIO_PIN_0);
  delay(700);
  GPIO_WriteLow(GPIOE, GPIO_PIN_0);
}

uint8_t check_M66(void)
{
  tx_command(ATI);
  //delay(300);
  //memcpy(data, get_command_answer(AT), answers[AT].answer_len);
  return check_answer(ATI, data);
}

uint8_t init_state_machine(void)
{
  init_GPIO();
  init_UART2();
  turn_on_M66();
  //delay(50);
  return check_M66();
  //return 0;
}