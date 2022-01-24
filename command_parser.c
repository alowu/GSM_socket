#include "command_parser.h"
#include "tim4_millis.h"
#include "rele.h"

extern uint8_t r_data[128];
extern uint8_t t_data[26];

extern uint8_t rx_buffer_position;
extern uint8_t rx_buffer_size;
extern uint8_t rx_buffer[128];

extern uint8_t tx_buffer_position;
extern uint8_t tx_buffer_size;
extern uint8_t tx_buffer[26];

extern uint8_t counter;

extern uint8_t number[13];

uint8_t answer_copied = 1;
uint8_t number_set = 0;

extern uint8_t request_set_number;

void set_command(command_name_e name)
{
  uint8_t *command = commands[name].value;
  size_t command_len = commands[name].command_len;
  memcpy(tx_buffer, command, command_len);
}

uint8_t *get_command_answer(command_name_e name)
{
  uint8_t *answer = NULL;
  memcpy(answer, rx_buffer, answers[name].answer_len);
  return answer;
}

void tx_command(command_name_e name)
{
  set_command(name);
  
  tx_buffer_position = 0;
  tx_buffer_size = commands[name].command_len;
  
  UART2_ITConfig(UART2_IT_TXE, ENABLE);
}   

uint32_t tick = 0;

uint8_t check_answer(command_name_e name, uint8_t *answer)
{
 if (answer_copied == 0)
 {
  uint8_t result;
  uint8_t *expected_answer = answers[name].value;
  uint8_t answer_len = answers[name].answer_len;
  switch (name) 
  {
    case AT:
    {
      result = memcmp(expected_answer, answer, answer_len);
      break; 
    }
    case RING:
    {
      result = memcmp(expected_answer, answer, answer_len);
      break;
    }
    case CLIP:
    {
      result = memcmp(expected_answer, answer, answer_len);
      if (result == 0)
      {
        char *p = strstr((char*)answer, "+375447876908");
        if (p)
        {
          result = 0;
        }
        else 
        {
          result = 1;
        }
      }
      break;
    }
    default:
    {
      result = 1;
      break;
    }
  }
  answer_copied = 1;
  return result;
 }
 else 
 {
   return answer_copied;
 }
}

uint8_t check_number(void)
{  
  char *p = strstr((char*)r_data, "+375447876908");
  if (p)
  {
    return 1;
  }
  else 
  {
    return 0;
  }
}

void command_state_machine(void)
{
  
}