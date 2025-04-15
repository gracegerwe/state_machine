#include <stdio.h>
#include <string.h>

#include "actuator.h"
#include "hal.h"

#define MAX_ACTUATORS 2

static Actuator actuators[MAX_ACTUATORS] = {
    {.name = "valve1",
     .state = IDLE,
     .position = 0,
     .target = 0,
     .unchanged_cycles = 0,
     .is_stuck = 0},
    {.name = "valve2",
     .state = IDLE,
     .position = 0,
     .target = 0,
     .unchanged_cycles = 0,
     .is_stuck = 0},
};

void hal_init() {
  // Nothing needed yet
}

static Actuator* get_actuator(const char* name) {
  for (int i = 0; i < MAX_ACTUATORS; i++) {
    if (strcmp(name, actuators[i].name) == 0) return &actuators[i];
  }
  return NULL;
}

void hal_set_target(const char* name, int position) {
  Actuator* a = get_actuator(name);
  if (a) {
    a->target = position;
    a->state = MOVING;
  }
}

void hal_tick() {
  for (int i = 0; i < MAX_ACTUATORS; i++) {
    Actuator* a = &actuators[i];

    if (a->state == MOVING) {
      printf("🟢 %s: Position %d → Target %d\n", a->name, a->position,
             a->target);

      int prev = a->position;
      if (!a->is_stuck) {
        if (a->position < a->target)
          a->position++;
        else if (a->position > a->target)
          a->position--;
      }

      if (a->position == prev)
        a->unchanged_cycles++;
      else
        a->unchanged_cycles = 0;

      if (a->unchanged_cycles > 5) {
        a->state = FAULT;
        printf("🚨 %s FAULT: stuck actuator\n", a->name);
      }

      if (a->position == a->target && a->state != FAULT) {
        printf("✅ %s: Reached target\n", a->name);
        a->state = IDLE;
      }
    }
  }
}

void hal_inject_fault(const char* name) {
  Actuator* a = get_actuator(name);
  if (a) a->is_stuck = 1;
}

void hal_reset_fault(const char* name) {
  Actuator* a = get_actuator(name);
  if (a && a->state == FAULT) {
    a->is_stuck = 0;
    a->unchanged_cycles = 0;
    a->state = IDLE;
    printf("✅ %s fault cleared.\n", a->name);
  }
}

void hal_print_status() {
  for (int i = 0; i < MAX_ACTUATORS; i++) {
    Actuator* a = &actuators[i];
    printf("ℹ️  %s → Pos: %d, Target: %d, State: %s\n", a->name, a->position,
           a->target,
           a->state == IDLE     ? "IDLE"
           : a->state == MOVING ? "MOVING"
           : a->state == FAULT  ? "FAULT"
                                : "UNKNOWN");
  }
}
