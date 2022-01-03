#include "init_socket.h"
#include "tim4_millis.h"

extern uint8_t r_data[26];

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
  tx_command(AT);
  return check_answer(AT, r_data);
}

void initialize_peripherals(void)
{
  CLK_DeInit();
  init_TIM4();
  init_GPIO();
  init_UART2();
}

void initialize_M66(void)
{
  while(1)
  {
    delay(500);
    GPIO_WriteHigh(GPIOG, GPIO_PIN_0);
    turn_on_M66();
    uint8_t is_ready = 1;
    for (uint8_t i = 0; i < 10; i++)
    {
      is_ready = check_M66();
      if (is_ready == 0)
      {
        break;
      }
      delay(700);
    }
    if (is_ready == 0)
    {
      GPIO_WriteLow(GPIOG, GPIO_PIN_0);
      break;
    }
    GPIO_WriteLow(GPIOG, GPIO_PIN_0);
    delay(500);
  }
}