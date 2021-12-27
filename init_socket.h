#ifndef INIT_SOCKET_H
#define INIT_SOCKET_H

#include "command_parser.h"
#include "uart.h"
#include "stm8s_gpio.h"

void init_GPIO(void);
void turn_on_M66(void);
uint8_t check_M66(void);

uint8_t init_state_machine(void);

void test(void);

#endif