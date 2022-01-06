#include <stdio.h>

#include "stack.h"
#include "automaton.h"

/* @requires: s1 and s2 valid pointers
 * @assigns:
 * @ensures: returns 1 if the strings are the same and 0 otherwise
 */
int CompareString(char* s1, char* s2)
{
	int i = 0;
	while(s1[i] != '\0' || s2[i] != '\0')
	{
		if(s1[i] == s2[i])
			i++;
		else
			return 0;
	}
	return 1;
}

int main(int argc, char** argv)
{
	if(argc < 2 || argc == 3 || argc > 4)
	{
		printf("Incorrect number of arguements, correct usage is ./automaton filename.aut [-g dotfile.dot]\n");
		return 6;
	}


	Automaton aut = ParseAutomaton(argv[1]);
	printf("File \"%s\" read correctly.\n", argv[1]);

	if(argc == 4)
	{

		if(!CompareString(argv[2], "-g"))
		{
			printf("Incorrect number of arguements, correct usage is ./automaton filename.aut [-g dotfile.dot]\n");
			return 6;
		}
		CreateDOT(aut, argv[3]);
		return 0;
	}
	char buf[256];

	// the loop stops when the user enters an empty line
	while(1)
	{
		printf("Please enter your input:\n");
		fgets(buf, 256, stdin);

		if(CompareString(buf, "\n"))
			return 0;

		Stack s = CreateStack();
		int errorPos = 0;
		Push(0, &s);
		if(Execute(aut, &s, buf, &errorPos))
			printf("Accepted\n");
		else
			printf("Rejected, at character #%i %c\n", errorPos + 1, buf[errorPos]);
	}

	return 0;

}










