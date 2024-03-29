#ifndef COMMAND_PARSER_H
#define COMMAND_PARSER_H

#include "uart.h"

#define MAX_COMMAND_LEN 15

typedef enum
{
  AT,
  ATI
} command_name_e;

typedef struct
{
  command_name_e name;
  uint8_t value[MAX_COMMAND_LEN];
  uint8_t command_len;
  uint8_t max_answer_len;
} commands_t;

static commands_t commands[] = {
  {AT, "AT\r\n", 4, 4},
  {ATI, "ATI\r\n", 5, 51}
};

void set_command(command_name_e name);
uint8_t *get_command(void);

void tx_command(void);

void command_state_machine(void);

#endif