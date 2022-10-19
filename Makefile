DEBUG="-v -da -Q"

all: 
	gcc donut.c -o donut -lm 
	gcc cube.c -o cube -lm  
	gcc pyramid.c -o pyramid -lm 

	./pyramid

debug:
	gcc donut.c -o gonut -lm $(DEBUGFLAGS)
	gcc cube.c -o cube -lm $(DEBUGFLAGS)
	gcc pyramid.c -o pyramid $(DEBUGFLAGS)

	./pyramid
