#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "headers/structures.h"
#include "headers/file_handler.h"
#include "headers/commands.h"

#define FILENAME "tododata"

void p_alloc_error(void){
	printf("Allocation error\n");
}

void p_invalid_command(void){
	printf("Invalid command. try 'todo commands' to see possible commands\n");
}

void p_error(const char* _description){
	printf("ERROR: %s\n", _description);
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

	/*
	-------------------------------
	----------USER INPUTS----------
	-------------------------------
	*/
	//user entered no argument
	if(argc == 1){
		if(!todo_show_items(FILENAME, head->n_incomplete, head->n_complete, "incomplete")){
			printf("ERROR: failed to show incomplete items\n");
			return 1;
		}
		return 0;
	}
	//if user entered arguments
	else{
	
		if(strcmp(args[1], "commands") == 0){
			todo_commands();
		}
		
		else if(strcmp(args[1], "destroy") == 0){
			if(!todo_destroy(FILENAME)){
				printf("ERROR: failed to destroy todofile\n");
				return 1;
			}
		}

		else if(strcmp(args[1], "add") == 0){
			if(!todo_add_itemname(FILENAME, head, args[2])){
				printf("ERROR: failed to add item\n");
				return 1;
			}
			printf("Added item successfully\n");
		}

		else if(strcmp(args[1], "complete") == 0){
			if(!todo_complete(FILENAME, head, args[2])){
				//perror("Failed to mark item complete. Are you sure such an item exists?");
				printf("ERROR: Failed to mark item complete. Are you sure such an item exists?\n");
				return 1;
			}
			printf("Successfully marked %s as complete\n", args[2]);
		}

		else if(strcmp(args[1], "all") == 0){
		    if(argc > 2){
		    printf("command 'all' takes no arguments\n");
		    return 0;
		    }
		    if(!todo_show_items(FILENAME, head->n_incomplete, head->n_complete, "all")){
		        printf("ERROR: Failed to show all items\n");
		        return 1;
		    }
		}

		else if(strcmp(args[1], "completed") == 0){
		    if(argc > 2){
		        printf("command 'completed' takes no arguments\n");
		        return 0;
		    }
		    if(!todo_show_items(FILENAME, head->n_incomplete, head->n_complete, "complete")){
		        printf("ERROR: Failed to show completed items\n");
		        return 1;
		    }
		}
		
		else{
		    printf("Invalid command\n");
		}
	}

	return 0;
}
