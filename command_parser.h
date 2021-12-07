#ifndef COMMAND_PARSER_H
#define COMMAND_PARSER_H

#include "uart.h"

#define MAX_COMMAND_LEN 15
#define MAX_ANSWER_LEN 256

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
} commands_t;

static commands_t commands[] = 
{
  {AT, "AT\r\n", 4},
  {ATI, "ATI\r\n", 5}
};

typedef struct
{
  command_name_e name;
  uint8_t answer_len;
  uint8_t value[MAX_ANSWER_LEN];
} answers_t;

static answers_t answers[] =
{
  {AT, 4, "OK\r\n"},
  {ATI, 13, "TEST ANSWER\r\n"}
};

void set_command(command_name_e name);
uint8_t *get_command_answer(command_name_e name);
void tx_command(command_name_e name);
uint8_t check_answer(command_name_e name, uint8_t *answer);

void command_state_machine(void);

#endif