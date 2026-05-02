#include "../headers/file_handler.h"

bool get_head(const char *_filepath, Head *_head){
	FILE *file = fopen(_filepath, "rb");
	if(!file) return false;

	Head *temp_head = malloc(sizeof(Head));
	if(!temp_head) return false;

	//go to begining of file
	fseek(file, 0, SEEK_SET);
	//read from file into temp_head
	size_t n_read = fread(temp_head, sizeof(Head), 1, file);
	//if successful set _head = temp_head
	if(n_read != 1){
		fclose(file);
		return false;
	}
	_head = temp_head;
	//close file
	fclose(file);
	//return true
	return true;
}

bool get_incomplete()
