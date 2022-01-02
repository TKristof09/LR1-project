#ifndef STACK_H
#define STACK_H

#include <stdlib.h>

struct Node
{
	char value;
	struct Node* next;
};
typedef struct Node* Stack;

int IsEmpty(Stack s);

void Push(char v, Stack* s);

char Pop(Stack* s);

char Peek(Stack s);

void PrintStack(Stack s);

#endif
