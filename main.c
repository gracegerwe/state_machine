#include <stdio.h>
#include <string.h>

#include "hal.h"

#define INPUT_BUF_SIZE 100

int main() {
  hal_init();
  char input_buf[INPUT_BUF_SIZE];

  printf(
      "🎮 Type commands like: open valve1 90, inject valve1, reset valve1, "
      "status, exit\n\n");

  while (1) {
    hal_tick();  // run logic per tick

    printf("> ");
    fflush(stdout);
    if (!fgets(input_buf, INPUT_BUF_SIZE, stdin)) continue;

    input_buf[strcspn(input_buf, "\n")] = 0;

    if (strncmp(input_buf, "exit", 4) == 0) break;

    char name[16];
    int val;
    if (sscanf(input_buf, "open %s %d", name, &val) == 2) {
      hal_set_target(name, val);
    } else if (sscanf(input_buf, "inject %s", name) == 1) {
      hal_inject_fault(name);
    } else if (sscanf(input_buf, "reset %s", name) == 1) {
      hal_reset_fault(name);
    } else if (strncmp(input_buf, "status", 6) == 0) {
      hal_print_status();
    } else {
      printf("❌ Unknown command.\n");
    }
  }

  return 0;
}
