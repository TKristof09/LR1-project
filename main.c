#include <stdio.h>
#include <errno.h>

#define REJETTE 0
#define ACCEPTE 1
#define DECALE 2
#define REDUIT 3

struct Transition
{
	// for decale/branchement value1 is the new state
	// for reduit value1 is n, value2 is A
	char type;
	char value;
};
typedef struct Transition Transition;

struct Automaton
{
	int num_states;
	Transition** transitions;	// size n* 128, usage: transitions[cur_state][character]

};
typedef struct Automaton Automaton;

Automaton ParseAutomaton(char* filename)
{
	Automaton res;


	FILE* f = fopen(filename, 'r');
	if(f == NULL)
	{
		perror("ERROR");
		exit(1);
	}
	int n;
	fscanf(f, "a %i\n", &n);

	// Allocate matrix for transitions
	res.num_states = n;
	res.transitions = malloc(n * sizeof(Transition*));
	for (int i = 0; i < n; i++)
	{
		res.transitions[i] = malloc(128 * sizeof(Transition));
	}


	char* buffer = malloc(n * 128);
	fread(buffer, 1, n * 128, f);
	// save actions
	for(int i = 0; i < 128; i++)
	{
		for(int j = 0; j < 128; j++)
		{
			switch(buffer[i * 128 + j])
			{
				case REJETTE:
				case ACCEPTE:
				case DECALE:
				case REDUIT: res.transitions[i][j].type = buffer[i * 128 + j]; break;
				default: printf("ERROR: action(%i, %i) instruction %i is invalid\n", i, j, buffer[i * 128 + j]); exit(2);
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

	}




	fclose(f);
}
