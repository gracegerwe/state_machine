#ifndef ACTUATOR_H
#define ACTUATOR_H

typedef enum { IDLE, MOVING, FAULT } State;

typedef struct {
  State state;
  int position;
  int target;
} Actuator;

#endif
