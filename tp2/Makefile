OPTIONS = -W -Wall -g
Link_OPT = -W -Wall -c
CC = g++

all : display_stack try_mul 

display_stack: display_stack.o
	$(CC) $(OPTIONS) -o display_stack display_stack.o

try_mul: try_mul.o try.o
	$(CC) $(OPTIONS) -o try_mul try_mul.o try.o

PointNode: PointNode.h Point.o Point.h

Point.o: Point.h

%.o : %.cpp
	$(CC) $(Link_OPT) $< 

clean:
	rm *.o *~ display_stack try_mul
