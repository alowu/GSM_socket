#include "command_parser.h"

#define COMMANDS_AMOUNT 2

extern uint8_t data[256];

extern uint8_t buffer_position;
extern uint8_t buffer_size;
extern uint8_t buffer[256];


void set_command(command_name_e name)
{
  uint8_t *command = commands[name].value;
  size_t command_len = commands[name].command_len;
  
  memcpy(data, command, command_len);
}

uint8_t *get_command(void) 
{
  uint8_t data_copy[256];
  memcpy(data_copy, data, 256);
  
  uint8_t *token = (uint8_t*)strtok((char*)data_copy, "\n");
  return token;
}


void tx_command(void)
{
  uint8_t *command = get_command();
  uint8_t size = strlen((char *)command);
  
  buffer_position = 0;
  buffer_size = size;
  
  UART2_ITConfig(UART2_IT_TXE, ENABLE);
}   

void command_state_machine(void)
{
  command_name_e name = AT;
  set_command(name);
  tx_command();
  rx_data(commands[name].max_answer_len);
  
  
}