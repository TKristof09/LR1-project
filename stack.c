#include "stack.h"
#include <stdio.h>

int IsEmpty(Stack s)
{
	return s == NULL;
}

void Push(char v, Stack* s)
{
	Stack news = (Stack)malloc(sizeof(struct Node));
	news->value = v;
	news->next = *s;

	*s = news;
}

char Pop(Stack* s)
{
	char res = (*s)->value;
	*s = (*s)->next;

	return res;
}

char Peek(Stack s)
{
	return s->value;
}

void PrintStack(Stack s)
{
	printf("Stack: ");
	while(s != NULL)
	{
		printf("%i -> ", s->value);
		s = s->next;
	}
	printf("END\n");
}
