.PHONY:all clean

CC = gcc

ROOTDIR=.

FLAGS = -g -o

all:pizza

pizza:pizza.o 
	$(CC) $(FLAGS) $@ $^  

%.o:%.c
	$(CC) -c $(FLAGS) $@ $<

clean:
	@ rm -fv *~ *.o *# pizza




readme:
	man ./man

man:
	man ./man
