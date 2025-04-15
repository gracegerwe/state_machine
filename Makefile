CC = gcc
CFLAGS = -Wall -Wextra

SRC = main.c hal.c
TARGET = state_machine

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $@ $(SRC)

clean:
	rm -f $(TARGET) *.o
