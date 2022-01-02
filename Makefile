OBJS	= main.o stack.o
SOURCE	= main.c stack.c
HEADER	= stack.h
OUT	= automaton
CC	 = gcc
FLAGS	 = -c -Wall -g

all: $(OBJS)
	$(CC) -g $(OBJS) -o $(OUT)

main.o: main.c
	$(CC) $(FLAGS) main.c

stack.o: stack.c
	$(CC) $(FLAGS) stack.c


clean:
	rm -f $(OBJS) $(OUT)
