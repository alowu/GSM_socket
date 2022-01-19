#ifndef COMMAND_PARSER_H
#define COMMAND_PARSER_H

#include "uart.h"

#define MAX_COMMAND_LEN 128
#define MAX_ANSWER_LEN 256

typedef enum
{
  AT,
  ATH,
  CLCC
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
  {ATH, "ATH\r\n", 5},
  {CLCC, "AT+CLCC\r\n", 9}
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
  {ATH, 0, ""},
  {CLCC, 5, "+CLCC"}//"+CLCC: 1,1,4,0,0,\"+375447876908\",145,\"\""}
};

void set_command(command_name_e name);
uint8_t *get_command_answer(command_name_e name);
void tx_command(command_name_e name);
uint8_t check_ring(void);
uint8_t check_answer(command_name_e name, uint8_t *answer);

void command_state_machine(void);

#endif