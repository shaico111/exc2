#pragma once
#include "Headers.h"

void Ex1();
char** split(char letter, char* str, int* p_size);
void printStringsArray(char** str_arr, int size);
void freeMatrix(void** A, int rows);