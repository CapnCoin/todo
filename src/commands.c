#include "../headers/commands.h"

bool todo_show_items(const char* _file_path, const size_t _n_incomplete, const size_t _n_complete, const char* _command){
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
				printf("Name:		-	%s\n", incomplete_items[i].name);
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
				printf("Name:		-	%s\n", complete_items[i].name);
				printf("Description:	-	%s\n", complete_items[i].description);
				printf("\n");
			}
		}
		else{
			printf("There are currently no complete items\n");
		}
	}
	//print all items
	else if(strcmp(_command, "all") == 0){
		printf("-----INCOMPLETE ITEMS-----\n");
		if(incomplete_items){
			for(size_t i = 0; i < _n_incomplete; i++){
				printf("Name:		-	%s\n", incomplete_items[i].name);
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
				printf("Name:		-	%s\n", complete_items[i].name);
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

bool todo_destroy(const char* _filename){
	if(!file_exists(_filename)){
		printf("This directory is already void of a todofile\n");
		return 0;
	}
	else{
		if(remove(_filename) != 0){
			printf("Failed to remove file. You can manually remove it by running 'rm .tododata' in the directory\n");
			return 1;
		}
		printf("tododata successfully removed\n");
		return 0;
	}
}

void todo_commands(void){
	printf("-----COMMANDS-----\n");
	printf("commands                 -     Shows all available commands\n");
	printf("init                     -     Initialises a todo list in the current working directory\n");
	printf("destroy                  -     Destroys the todofile in the current directory\n");
	printf("<no command>             -     Shows all incomplete items\n");
	printf("add <item name>          -     Adds a item with name <item name> to incomplete items\n");
	printf("complete <item name>     -     Mark a incomplete item as complete\n");
	printf("\n");
}

bool todo_add_itemname(const char* _filename, Head* _head, const char* _item_name){
	Item* incomplete_items;
	Item* complete_items;

	//allocate incomplete_items if needed
	if(_head->n_incomplete > 0){
		incomplete_items = malloc(sizeof(Item) * _head->n_incomplete);
		if(!incomplete_items) return false;
	}
	else incomplete_items = NULL;

	//allocate complete items if needed
	if(_head->n_complete > 0){
		complete_items = malloc(sizeof(Item) * _head->n_complete);
		if(!complete_items){
			free(incomplete_items);
			return false;
		}
	}
	else complete_items = NULL;

	//read from file into items
	if(!read_items(_filename, _head->n_incomplete, incomplete_items, _head->n_complete, complete_items)){
		free(incomplete_items);
		free(complete_items);
		return false;
	}
	//get a description from the user
	char description[MAX_DESC_SIZE];
	printf("Enter a description: ");
	if(!fgets(description, sizeof(description), stdin)){
		free(incomplete_items);
		free(complete_items);
		return false;
	}
	description[strcspn(description, "\n")] = '\0';
	
	//reallocate incomplete items to make room for the new item
	Item* temp_incomplete = realloc(incomplete_items, sizeof(Item) * (_head->n_incomplete + 1));
	if(!temp_incomplete){
		free(incomplete_items);
		free(complete_items);
		return false;
	}
	incomplete_items = temp_incomplete;
	
	//add name and description to new item
	size_t new_item_pos = _head->n_incomplete;
	strncpy(incomplete_items[new_item_pos].name, _item_name, MAX_NAME_SIZE);
	strncpy(incomplete_items[new_item_pos].description, description, MAX_DESC_SIZE);
	//increment head->n_incomplete
	_head->n_incomplete++;
	//write to file
	if(!write_file(_filename, _head, incomplete_items, complete_items)){
		free(incomplete_items);
		free(complete_items);
		return false;
	}

	free(incomplete_items);
	free(complete_items);
	return true;
}

bool todo_complete(const char* _filename, Head* _head, const char* _item_name){
	if(!(_head->n_incomplete > 0)) return false;
	
	Item* incomplete_items;
	Item* complete_items;

	//allocate incomplete items if needed
	if(_head->n_incomplete > 0){
		incomplete_items = malloc(sizeof(Item) * _head->n_incomplete);
		if(!incomplete_items) return false;
	}
	else incomplete_items = NULL;

	//allocate complete items if needed
	if(_head->n_complete > 0){
		complete_items = malloc(sizeof(Item) * _head->n_complete);
		if(!complete_items){
			if(incomplete_items) free(incomplete_items);
			return false;
		}
	}
	else complete_items = NULL;

	//read from file into items
	if(!read_items(_filename, _head->n_incomplete, incomplete_items, _head->n_complete, complete_items)){
		if(incomplete_items) free(incomplete_items);
		if(complete_items) free(complete_items);
		return false;
	}

	//loop through incomplete items and look for one with name _item_name
	
	for(size_t i = 0; i < _head->n_incomplete; i++){
		if(strcmp(incomplete_items[i].name, _item_name) == 0){
			//resize complete items and insert values
			Item* temp_complete = realloc(complete_items, sizeof(Item) * (_head->n_complete + 1));
			if(!temp_complete){
				if(incomplete_items) free(incomplete_items);
				if(complete_items) free(complete_items);
				return false;
			}
			complete_items = temp_complete;

			//copy name and description to new complete item
			strncpy(complete_items[_head->n_complete].name, incomplete_items[i].name, MAX_NAME_SIZE);
			strncpy(complete_items[_head->n_complete].description, incomplete_items[i].description, MAX_DESC_SIZE);
			_head->n_complete++;

			//remove the item from incomplete items
			int num_items_to_move = _head->n_incomplete - i - 1;

			if(num_items_to_move > 0){
				memmove(&incomplete_items[i], &incomplete_items[i + 1], (num_items_to_move * sizeof(Item)));
				
			}
			_head->n_incomplete--;
			incomplete_items = realloc(incomplete_items, sizeof(Item) * _head->n_incomplete);

			//write file
			if(!write_file(_filename, _head, incomplete_items, complete_items)){
				free(incomplete_items);
				free(complete_items);
				return false;
			}

			free(incomplete_items);
			free(complete_items);
			return true;
		}
	}

	if(incomplete_items) free(incomplete_items);
	if(complete_items) free(complete_items);
	return false;
}
