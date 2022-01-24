#include "rele.h"

uint8_t rele_enable = 0;

uint8_t get_rele_state(void)
{
  return rele_enable;
}

void set_rele_enable(void)
{
  rele_enable = 1;
}

void set_rele_disable(void)
{
  rele_enable = 0;
}