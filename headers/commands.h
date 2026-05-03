#pragma once

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "file_handler.h"
#include "structures.h"

bool todo_show_items(const char* _file_path, const size_t _n_incomplete, const size_t _n_complete, const char* _command);

bool todo_destroy(const char* _filename);

void todo_commands(void);

bool todo_add_itemname(const char* _filename, Head* _head, const char* _item_name);

bool todo_complete(const char* _filename, Head* _head, const char* _item_name);
