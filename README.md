# state_machine

Minimal C simulation of a safety-critical actuator control state machine.

This project simulates an actuator (e.g. motor or valve) moving toward a target using basic firmware concepts like state machines, control loops, and safety states.

## 💡 features
- Three states: IDLE, MOVING, FAULT
- Simulated actuator that increments/decrements position toward target
- Logs system status to console
- Ready to expand with faults, safety checks, and hardware ports
- Designed to scale from virtual to real-world microcontroller firmware (e.g., Arduino, STM32).

## 🛠 build & run

```bash
make
./state_machine