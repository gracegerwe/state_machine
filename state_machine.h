#ifndef STATE_MACHINE_H
#define STATE_MACHINE_H

#include <stdio.h>

#include "actuator.h"
#include "state_machine.h"

void update_state_machine(Actuator *a) {
  switch (a->state) {
    case IDLE:
      printf("🟡 IDLE: Waiting for command...\n");
      if (a->target != a->position) {
        a->state = MOVING;
      }
      break;

    case MOVING:
      printf("🟢 MOVING: Position %d → Target %d\n", a->position, a->target);
      if (a->position < a->target) {
        a->position++;
      } else if (a->position > a->target) {
        a->position--;
      } else {
        printf("✅ Reached target!\n");
        a->state = IDLE;
      }
      break;

    case FAULT:
      printf("🔴 FAULT: System halted.\n");
      break;
  }
}

#endif
