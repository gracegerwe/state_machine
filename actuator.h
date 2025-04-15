#ifndef ACTUATOR_H
#define ACTUATOR_H

typedef enum { IDLE, MOVING, FAULT } State;

typedef struct {
  const char* name;
  State state;
  int position;
  int target;
  int unchanged_cycles;
  int is_stuck;
} Actuator;

#endif
