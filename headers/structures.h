#pragma once
#include <stdlib.h>

#define MAX_NAME_SIZE 255
#define MAX_DESC_SIZE 1024

typedef struct Head{
	size_t n_incomplete;
	size_t n_complete;
}Head;

typedef struct Item{
	char name[MAX_NAME_SIZE];
	char description[MAX_DESC_SIZE];
}Item;
