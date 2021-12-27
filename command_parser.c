#include "command_parser.h"
#include "tim4_millis.h"

extern uint8_t data[26];

extern uint8_t rx_buffer_position;
extern uint8_t rx_buffer_size;
extern uint8_t rx_buffer[26];

extern uint8_t tx_buffer_position;
extern uint8_t tx_buffer_size;
extern uint8_t tx_buffer[26];

extern uint8_t counter;

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
  
  size_t command_len = commands[name].command_len;
  size_t answer_len = answers[name].answer_len;
  
  tx_buffer_position = 0;
  tx_buffer_size = command_len;
  
  UART2_ITConfig(UART2_IT_TXE, ENABLE);
   
  while(counter < command_len)
  {
  }
  counter = 0;
  rx_data(answer_len);
}   

uint8_t check_answer(command_name_e name, uint8_t *answer)
{
  uint8_t result;
  uint8_t *expected_answer = answers[name].value;
  uint8_t answer_len = answers[name].answer_len;
  tx_data(answer, answer_len);
  switch (name) 
  {
    case AT:
    {
      //memcpy(expected_answer, answers[name].value, answer_len);
      result = memcmp(expected_answer, answer, answer_len);
      break; 
    }
    case ATI:
    {
      memcpy(expected_answer, answers[name].value, answer_len);
      result = memcmp(expected_answer, answer, answer_len);
      break;
    }
    default:
    {
      result = 1;
      break;
    }
  }
  return result;
}

void command_state_machine(void)
{
  
}