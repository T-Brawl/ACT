OPTIONS = -W  -g 
Link_OPT = -W -Wall -Werror -g -c -Wpedantic
CC = gcc

all : main

main:main.c
	$(CC) $(OPTIONS) -o main main.c

%.o : %.c
	$(CC) $(Link_OPT) $< 

clean:
	rm *.o *~ svg
