#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "headers/structures.h"
#include "headers/file_handler.h"

#define FILENAME "tododata"

/*

ADD INIT FILE FUNCTION

*/


void p_alloc_error(void){
	printf("Allocation error\n");
}

void p_invalid_command(void){
	printf("Invalid command. try 'todo commands' to see possible commands\n");
}

void p_commands(void){
	printf("-----COMMANDS-----\n");
	printf("commands		-	shows all available commands\n");
	printf("init			-	initialises a todo list in the current working directory");
}

int main(int argc, char **args){
	//check if file exists
	if(!file_exists(FILENAME)){
		printf("Could not file a todofile. Try 'todo init'\n");
		return 1;
	}
	
	//allocate head
	Head* head = malloc(sizeof(Head));
	if(!head){
		p_alloc_error();
	}
	//read head from file
	if(!read_head(FILENAME, head)){
		printf("Error reading head from file");
	}
		
	switch (argc){
		//user hasnt passed any args
		case 1:
			
			break;

		//user passed 1 args
		case 2:
			if(strcmp(args[1], "commands")){
				p_commands();
				return 0;
			}
			else if(strcmp(args[1], "init")){
				init_file(FILENAME);
			}
			else{
				p_invalid_command();
			}
			break;

		//user passed 2 args
		case 3:

			break;

		default:
			break;
	}

	printf("%d\n", argc);
	printf("Hello from todo\n");

	return 0;
}
