#ifndef COMMAND_PARSER_H
#define COMMAND_PARSER_H

#include "uart.h"

#define MAX_COMMAND_LEN 15
#define MAX_ANSWER_LEN 256

typedef enum
{
  AT,
  ATI,
  CPIN,
  QINISTAT
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
  {ATI, "ATI\r\n", 11},
  {CPIN, "AT+CPIN?\r\n", 10},
  {QINISTAT, "AT+QINISTAT\r\n", 13}
};

typedef struct
{
  command_name_e name;
  uint8_t answer_len;
  uint8_t value[MAX_ANSWER_LEN];
} answers_t;

static answers_t answers[] =
{
  {AT, 3, "OK\r"},
  {ATI, 13, "TEST ANSWER\r\n"},
  {CPIN, 18, "+CPIN: READY\r\nOK\r\n"},
  {QINISTAT, 12, "+QINISTAT: "} // 11 is letters + 1 <state> number
};

void set_command(command_name_e name);
uint8_t *get_command_answer(command_name_e name);
void tx_command(command_name_e name);
uint8_t check_answer(command_name_e name, uint8_t *answer);

void command_state_machine(void);

#endif