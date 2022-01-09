OUT	= automaton
OBJS	= main.o stack.o automaton.o
CC	 = gcc -Wall

all: $(OBJS)
	$(CC) $(OBJS) -o $(OUT)

main.o: main.c automaton.h stack.h
	$(CC) -c main.c

stack.o: stack.c stack.h
	$(CC) -c stack.c

automaton.o: stack.o automaton.h
	$(CC) -c automaton.c


clean:
	rm -f $(OBJS) $(OUT)
