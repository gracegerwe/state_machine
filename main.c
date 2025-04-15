#include <stdio.h>

#include "actuator.h"
#include "state_machine.h"

int main() {
  Actuator a = {.state = IDLE, .position = 0, .target = 0};

  for (int t = 0; t < 30; t++) {
    if (t == 5) {
      a.target = 10;
      printf("\n📨 Command received: Move to 10\n");
    }

    update_state_machine(&a);
  }

  return 0;
}
