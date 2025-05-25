#pragma once
#include "Headers.h"

void Ex1();
char** split(char letter, char* str, int* p_size);
void printStringsArray(char** str_arr, int size);
void freeMatrix(void** A, int rows);

// new helper functions
void input_word(int* i, int* counter, char* str, char*** ArrayOfWords, int* p_size);
void skip_spaces(int* i, char* str);
void skip_word(int* i, char* str);