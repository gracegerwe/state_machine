#include <stdio.h>
#include <string.h>

#include "actuator.h"
#include "state_machine.h"

#define INPUT_BUF_SIZE 100

int main() {
  Actuator a = {.state = IDLE, .position = 0, .target = 0};
  int user_input;

  char input_buf[INPUT_BUF_SIZE];

  while (1) {
    if (a.state == IDLE && a.position == a.target) {
      printf(
          "Enter a number between 0 and 180 to set a new actuator target or "
          "type 'exit': ");
      fflush(stdout);

      if (fgets(input_buf, INPUT_BUF_SIZE, stdin)) {
        // Remove newline if present
        input_buf[strcspn(input_buf, "\n")] = 0;

        if (strcmp(input_buf, "exit") == 0 || strcmp(input_buf, "q") == 0) {
          printf("👋 Exiting.\n");
          break;
        }

        int user_input;
        if (sscanf(input_buf, "%d", &user_input) == 1) {
          if (user_input >= 0 && user_input <= 180) {
            a.target = user_input;
            printf("📨 Command received: Move to %d degrees\n", user_input);
          } else {
            printf("❌ Out of range. Please enter a number from 0 to 180.\n");
          }
        } else {
          printf("⚠️ Invalid input. Please enter a number or type 'exit'.\n");
        }
      }
    }

    update_state_machine(&a);
  }

  return 0;
}
