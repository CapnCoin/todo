#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "headers/structures.h"
#include "headers/file_handler.h"

#define FILENAME "tododata"

void p_alloc_error(void){
	printf("Allocation error\n");
}

void p_invalid_command(void){
	printf("Invalid command. try 'todo commands' to see possible commands\n");
}

void commands(void){
	printf("-----COMMANDS-----\n");
	printf("commands		-	Shows all available commands\n");
	printf("init			-	Initialises a todo list in the current working directory");
	printf("\n");
}

int main(int argc, char **args){
	if(argc == 2 && strcmp(args[1], "init") == 0){
		if(file_exists(FILENAME)){
			printf("You already have a todofile in this directory.\n");
			return 0;
		}
		else if(init_file(FILENAME)){
			printf("Successfully initialised todo in this directory.\n");
			return 0;
		}
		return 1;
	}
	
	//check if file exists
	if(!file_exists(FILENAME)){
		printf("Could not find a todofile. Try 'todo init'\n");
		return 1;
	}
	
	//allocate head
	Head* head = malloc(sizeof(Head));
	if(!head){
		p_alloc_error();
		return 1;
	}
	//read head from file
	if(!read_head(FILENAME, head)){
		printf("Error reading head from file");
		return 1;
	}

	//user entered no argument
	if(argc == 1){
		
	}
	//user entered one argument
	else if(argc == 2){
		//commands
		if(strcmp(args[1], "commands") == 0){
			commands();
		}
		else{
			p_invalid_command();
		}
	}
	else if(argc == 3){
		
	}

	return 0;
}
