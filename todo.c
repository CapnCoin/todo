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

void todo_commands(void){
	printf("-----COMMANDS-----\n");
	printf("commands		-	Shows all available commands\n");
	printf("init			-	Initialises a todo list in the current working directory");
	printf("destroy			-	Destroys the todofile in the current directory");
	printf("<no command>	-	Shows all incomplete items");
	printf("\n");
}

bool show_items(const char* _file_path, const size_t _n_incomplete, const size_t _n_complete, const char* _command){
	//allocate memory for incomplete and complete items
	Item* incomplete_items;
	Item* complete_items;

	//allocate incomplete items if needed
	if(_n_incomplete > 0){
		incomplete_items = malloc(sizeof(Item) * _n_incomplete);
		if(!incomplete_items) return false;
	}
	else{
		incomplete_items = NULL;
	}

	//allocate complete items if needed
	if(_n_complete > 0){
		complete_items = malloc(sizeof(Item) * _n_complete);
		if(!complete_items){
			if(incomplete_items) free(incomplete_items);
			return false;
		}
	}
	else{
		complete_items = NULL;
	}

	//read file content into items
	if(!read_items(_file_path, _n_incomplete, incomplete_items, _n_complete, complete_items)){
		free(incomplete_items);
		free(complete_items);
		return false;
	}

	//print incomplete items
	if(strcmp(_command, "incomplete") == 0){
		if(incomplete_items){
			printf("-----INCOMPLETE ITEMS-----\n");
			for(size_t i = 0; i < _n_incomplete; i++){
				printf("Name:			-	%s\n", incomplete_items[i].name);
				printf("Description:	-	%s\n", incomplete_items[i].description);
				printf("\n");
			}
		}
		else{
			printf("There are currently no incomplete items\n");
		}
	}
	//print complete items
	else if(strcmp(_command, "complete") == 0){
		if(complete_items){
			printf("-----COMPLETE ITEMS-----\n");
			for(size_t i = 0; i < _n_complete; i++){
				printf("Name:			-	%s\n", complete_items[i].name);
				printf("Description:	-	%s\n", complete_items[i].description);
				printf("\n");
			}
		}
	}
	//print all items
	else if(strcmp(_command, "all") == 0){
		printf("-----INCOMPLETE ITEMS-----\n");
		if(incomplete_items){
			for(size_t i = 0; i < _n_incomplete; i++){
				printf("Name:			-	%s\n", incomplete_items[i].name);
				printf("Description:	-	%s\n", incomplete_items[i].description);
				printf("\n");
			}
		}
		else{
			printf("None\n");
		}
		
		printf("\n");
		
		printf("-----COMPLETE ITEMS-----\n");
		if(complete_items){
			for(size_t i = 0; i < _n_complete; i++){
				printf("Name:			-	%s\n", complete_items[i].name);
				printf("Description:	-	%s\n", complete_items[i].description);
				printf("\n");
			}
		}
		else{
			printf("None\n");
		}
	}
	//invalid command
	else{
		free(incomplete_items);
		free(complete_items);
		return false;
	}

	free(incomplete_items);
	free(complete_items);
	return true;
}

bool todo_destroy(void){
	if(!file_exists(FILENAME)){
		printf("This directory is already void of a todofile\n");
		return 0;
	}
	else{
		if(remove(FILENAME) != 0){
			printf("Failed to remove file. You can manually remove it by running 'rm .tododata' in the directory\n");
			return 1;
		}
		printf("tododata successfully removed\n");
		return 0;
	}
}


/*

----------MAIN FUNCTION----------

*/
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

	----------USER INPUTS----------

	*/
	//user entered no argument
	if(argc == 1){
		show_items(FILENAME, head->n_incomplete, head->n_complete, "incomplete");
	}
	//user entered one argument
	else if(argc == 2){
		//commands
		if(strcmp(args[1], "commands") == 0){
			todo_commands();
		}
		else if(strcmp(args[1], "destroy") == 0){
			todo_destroy();
		}
		else{
			p_invalid_command();
		}
	}
	else if(argc == 3){
		
	}

	return 0;
}
