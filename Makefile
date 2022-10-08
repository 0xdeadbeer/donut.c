DEBUG="-v -da -Q"

all: 
	gcc donut.c -o donut -lm 
	./donut
debug:
	gcc donut.c -o gonut -lm $(DEBUGFLAGS)
	./circle
