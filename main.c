#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#include "stack.h"

#define REJETTE 0
#define ACCEPTE 1
#define DECALE 2
#define REDUIT 3


char* CharToLiteral(char c)
{
	char* res = malloc(4 * sizeof(char));
	switch(c)
	{
		case '\n': res[0] = '\\'; res[1] = '\\'; res[2] = 'n'; res[3] = '\0'; break;
		case '\t': res[0] = '\\'; res[1] = '\\'; res[2] = 't'; res[3] = '\0'; break;
		case '\0': res[0] = '\\'; res[1] = '\\'; res[2] = '0'; res[3] = '\0'; break;
		default: res[0] = c; res[1] = '\0';
	};
	return res;
}
typedef char State;
struct Reduce
{
	char k;
	char A;
};
typedef struct Reduce Reduce;

enum Type {REJECT, ACCEPT, SHIFT, REDUCE};
typedef enum Type Type;

struct Automaton
{
	int num_states;
	Type** types;
	State** shifts;	// size n* 128, usage: transitions[cur_state][character]
	Reduce* reduces; // size n, usage reduits[cur_state]
	State** branchings;

};
typedef struct Automaton Automaton;

Automaton ParseAutomaton(char* filename)
{
	Automaton res;


	FILE* f = fopen(filename, "r");
	if(f == NULL)
	{
		perror("ERROR");
		exit(1);
	}
	int n;
	fscanf(f, "a %i\n", &n);

	// Allocate arrays for transitions
	res.num_states = n;
	res.types = malloc(n * sizeof(Type*));
	res.shifts = malloc(n * sizeof(State*));
	res.reduces = malloc(n * sizeof(Reduce));
	res.branchings = malloc(n * sizeof(State*));
	for (int i = 0; i < n; i++)
	{
		res.shifts[i] = malloc(128 * sizeof(State));

		res.branchings[i] = malloc(128 * sizeof(State));

		res.types[i] = malloc(128 * sizeof(Type));
	}


	char* buffer = malloc(n * 128);
	fread(buffer, 1, n * 128, f);
	// save actions
	for(int s = 0; s < n; s++)
	{
		// default init the array
		res.reduces[s].k = -1;
		res.reduces[s].A = -1;

		for(int c = 0; c < 128; c++)
		{
			// default init the 3 arrays
			res.shifts[s][c] = -1;
			res.branchings[s][c] = -1;
			res.types[s][c] = -1;

			switch(buffer[s * 128 + c])
			{
				case REJECT:
				case ACCEPT:
				case SHIFT:
				case REDUCE: res.types[s][c] = buffer[s * 128 + c]; break;
				default: printf("ERROR: action(%i, %i) instruction %i is invalid\n", s, c, buffer[s * 128 + c]); exit(2);
			}
		}
	}
	fscanf(f, "\n");

	fread(buffer, 1, 2 * (n+1), f);

	// read reduit(s)
	for(int i = 0; i < n; i++)
	{
		int k = buffer[i];
		int A = buffer[i + (n+1)];

		res.reduces[i].k = k;
		res.reduces[i].A = A;
	}

	fscanf(f, "\n");

	// read decale(s,c)
	fread(buffer, sizeof(char), 3, f);
	while(buffer[0] != '\255' && buffer[1] != '\255' && buffer[2] != '\255')
	{
		State s = buffer[0];
		char c = buffer[1];
		State ss = buffer[2];

		res.shifts[s][c] = ss;

		fread(buffer, sizeof(char), 3, f);

	}


	// read branchement(s,A)
	fread(buffer, sizeof(char), 3, f);
	while(buffer[0] != '\255' && buffer[1] != '\255' && buffer[2] != '\255')
	{
		State s = buffer[0];
		char A = buffer[1];
		State ss = buffer[2];

		res.branchings[s][A] = ss;

		fread(buffer, sizeof(char), 3, f);
	}


	free(buffer);
	fclose(f);


	return res;
}


void CreateDOT(Automaton aut, char* filename)
{
	FILE* f = fopen(filename, "w");

	fprintf(f, "digraph {\n");

	for(int i = 0; i < aut.num_states; i++)
	{
		if(aut.reduces[i].k != -1)
			fprintf(f, "r%i[label=\"(%i, %c)\"; shape=plain; fontcolor=blue];\n", i, aut.reduces[i].k, aut.reduces[i].A);
	}
	fprintf(f, "acc[label=\"Accept\"; shape=plain; fontcolor=green];\n");


	for(int s = 0; s < aut.num_states; s++)
	{
		for(int c = 0; c < 128; c++)
		{
			char* str = CharToLiteral(c);
			switch(aut.types[s][c])
			{
				case REJECT:
					break;
				case ACCEPT:
					fprintf(f, "Q%i -> acc[label=\"%s\"; color=green; fontcolor=green];\n", s, str);
					break;
				case SHIFT:
					fprintf(f, "Q%i -> Q%i[label=\"%s\"];\n", s, aut.shifts[s][c], str);
					break;
				case REDUCE:
					fprintf(f, "Q%i -> r%i[label=\"%s\"; color=blue];\n", s, s, str);
					break;
				default:
					exit(-2);

			}
			if(aut.branchings[s][c] != -1)
			{
				fprintf(f, "Q%i -> Q%i[label=\"%s\"; color=red; fontcolor=red];\n", s, aut.branchings[s][c], str);
			}

			free(str);
		}
	}
	fprintf(f, "}");
	fclose(f);
}

int Execute(Automaton aut, Stack* s, char* text)
{
	PrintStack(*s);
	State cur_state = Peek(*s);

	State cur_letter = text[0];


	State new_state = -1;

	char* str = CharToLiteral(cur_letter);
	printf("State: %i Char: %s Type: %i\n", cur_state, str, aut.types[cur_state][cur_letter]);
	free(str);

	switch(aut.types[cur_state][cur_letter])
	{
		case REJECT:
			return -1;
		case ACCEPT:
			return 0;
		case SHIFT:
			new_state = aut.shifts[cur_state][cur_letter];
			Push(new_state, s);
			return Execute(aut, s, &text[1]);
		case REDUCE:
			{
				int k = aut.reduces[cur_state].k;
				char A = aut.reduces[cur_state].A;
				State ss = cur_state;
				for(int i = 0; i < k; i++)
				{
					Pop(s);
				}
				new_state = aut.branchings[Peek(*s)][A];
				Push(new_state, s);
				return Execute(aut, s, text);
			}
		default:
			exit(-1);
	}
}

int main(int argc, char** argv)
{
	Automaton aut = ParseAutomaton(argv[1]);
	CreateDOT(aut, "aut.txt");
	char buf[256];
	fgets(buf, 256, stdin);
	//char text[20];
	//sscanf(buf, "%s", text);

	Stack s = NULL;
	Push(0, &s);
	int res = Execute(aut, &s, buf);

	printf("%i\n", res);
	return 0;

}










