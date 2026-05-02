#pragma once
#include <stdlib.h>

#define MAX_NAME_SIZE 255
#define MAX_DESC_SIZE 1024

typedef struct Head{
	size_t n_incomplete;
	size_t n_complete;
	size_t incomplete_offset;
	size_t complete_offset;
}Head;

typedef struct Item{
	char name[MAX_NAME_SIZE];
	char decription[MAX_DESC_SIZE];
}Item;
