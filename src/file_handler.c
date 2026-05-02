#include "../headers/file_handler.h"

bool init_file(const char* _file_name){
	FILE* file = fopen(_file_name, "wb");
	if(!file) return false;

	Head* head = malloc(sizeof(head));
	if(!head){
		fclose(file);
		return false;
	}

	head->n_incomplete = 0;
	head->n_complete = 0;

	fwrite(head, sizeof(Head), 1, file);

	fclose(file);
	return true;
}

bool file_exists(const char *filename){
    // F_OK is a constant that checks for the "existence" of the file
    if (access(filename, F_OK) == 0) {
        return true;
    }
    return false;
}

bool read_head(const char* _file_path, Head* _head){
	FILE* file = fopen(_file_path, "rb");
	if(!file) return false;

	if(fread(_head, sizeof(Head), 1, file) != 1){
		fclose(file);
		return false;
	}

	fclose(file);
	return true;
}

bool read_items(const char* _file_path, const size_t n_incomplete, Item* _incomplete_items, const size_t n_complete, Item* _complete_items){
	FILE* file = fopen(_file_path, "rb");
	if(!file) return false;

	//go to where items start
	fseek(file, sizeof(Head), SEEK_SET);
	
	//read incomplete items if there are any
	if(n_incomplete > 0){
		if(fread(_incomplete_items, sizeof(Item), n_incomplete, file) != n_incomplete){
			fclose(file);
			return false;
		}
	}

	//read complete items if there are any
	if(n_complete > 0){
		if(fread(_complete_items, sizeof(Item), n_complete, file) != n_complete){
			fclose(file);
			return false;
		}
	}

	fclose(file);
	return true;
}
