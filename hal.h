#ifndef HAL_H
#define HAL_H

#include "actuator.h"

void hal_init();
void hal_set_target(const char* name, int position);
void hal_tick();  // called every loop to simulate actuator movement
void hal_inject_fault(const char* name);
void hal_reset_fault(const char* name);
void hal_print_status();

#endif
