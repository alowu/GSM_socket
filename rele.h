#ifndef RELE_H
#define RELE_H

#include "command_parser.h"

extern uint8_t rele_enable;

uint8_t get_rele_state(void);
void set_rele_enable(void);
void set_rele_disable(void);


#endif