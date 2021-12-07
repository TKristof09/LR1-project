#include <stdlib.h>

struct Node
{
	char value;
	struct Node* next;
};
typedef struct Node* Stack;

int IsEmpty(Stack s)
{
	return s == NULL;
}

void Push(char v, Stack* s)
{
	Stack news = (Stack)malloc(sizeof(Node));
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

