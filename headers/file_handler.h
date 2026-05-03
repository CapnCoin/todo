#pragma once

#include "structures.h"
#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>

bool init_file(const char* _file_name);

bool read_head(const char* _file_path, Head* _head);

bool read_items(const char* _file_path, const size_t n_incomplete, Item* _incomplete_items, const size_t n_complete, Item* _complete_items);

bool file_exists(const char *filename);

bool write_file(const char* _filename, Head* _head, Item* _incomplete_items, Item* _complete_items);
