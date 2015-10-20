.PHONY:all clean

CC = gcc

FLAGS = -g -o

all:position

position:position.o
	$(CC) $(FLAGS) $@ $^ 

%.o:%.c
	$(CC) -c $(FLAGS) $@ $<

clean:
	@ rm -fv *~ *.o *# position

readme:
	man ./man

man:
	man ./man
