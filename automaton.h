#ifndef _AUTOMATON_H
#define _AUTOMATON_H

#include "stack.h"
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



/* @requires: filename a valid pointer
 * @assigns:
 * @ensures: parses the automaton from the file and returns it
 * */
Automaton ParseAutomaton(char* filename);

/* @requires: aut a valid automaton and filename a valid pointer
 * @assigns:
 * @ensures: creates a DOT file in the file filenname to visualise the automaton aut
 * */
void CreateDOT(Automaton aut, char* filename);

/* @requires: aut a valid automaton, s a pointer to a valid stack, text a valid pointer
 * @assigns: *s if the stack needs to be updated, and outErrorPos to the position of the letter where the error was in case the text got rejected
 * @ensures: executes the automaton aut, returns 0 if the text was rejected, 1 if accepted
 */
int Execute(Automaton aut, Stack* s, char* text, int* outErrorPos);

#endif
