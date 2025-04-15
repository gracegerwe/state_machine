all: state_machine

state_machine: main.c
	@gcc -o state_machine main.c
	@echo "✅ Build complete."

clean:
	rm -f state_machine