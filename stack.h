#ifndef STACK_H
#define STACK_H

#include <stdlib.h>

struct Node
{
	char value;
	struct Node* next;
};
typedef struct Node* Stack;

/* @requires:
 * @assigns:
 * @ensures: returns an empty stack
 */
Stack CreateStack();

/* @requires: s a valid stack
 * @assigns:
 * @ensures: returns 1 if s is empty 0 otherwise
 */
int IsEmpty(Stack s);

/* @requires: s a pointer to a valid stack
 * @assigns: new top of the stack to *s
 * @ensures: pushes the value v to the top of the stack s
 */
void Push(char v, Stack* s);

/* @requires: s a pointer to a valid stack
 * @assigns: new top of the stack to *s
 * @ensures: removes the top of the stack s and returns its value
 */
char Pop(Stack* s);

/* @requires: s a valid stack
 * @assigns:
 * @ensures: returns the value at the top of the stack without removing it
 */
char Peek(Stack s);

/* @requires: s a valid stack
 * @assigns:
 * @ensures: prints the stack
 */
void PrintStack(Stack s);

#endif
