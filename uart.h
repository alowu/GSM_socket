#ifndef UART_H
#define UART_H

#include "stm8s.h"
#include "stm8s_it.h"
#include <string.h>

void init_UART2(void);
void rx_data(uint8_t size);
void tx_data(uint8_t *data, uint8_t size);

#endif 