# LR1-project
Usage:
	./automaton automatonFilename [-g DOTfilename]

	Parses the automaton passed as argument and then ask the user for inputs to check whether the automaton accepts them or not
	To exit the program pass in a single line break when it asks for user input

	When -g flag is used the program creates a DOT file of the automaton passed as argument without executing the automaton

Error codes:  
	1: error reading the automaton file  
	2: automaton file is invalid  
	3: error during the execution of the automaton (due to incorrect parsing of the automaton file)  
	4: error in the automaton's transition types  
	5: error opening the file for creating the DOT file  
	6: invalid command line arguments  



