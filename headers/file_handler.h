#pragma once

#include "structures.h"
#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>

bool read_head(const char* _file_path, Head* _head);

bool read_items(const char* _file_path, const size_t n_incomplete, Item* _incomplete_items, const size_t n_complete, Item* _complete_items);

bool file_exists(const char *filename);
