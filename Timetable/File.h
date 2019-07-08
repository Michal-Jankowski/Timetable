#ifndef FILE_H
#define FILE_H
#include "List.h"
#include<stdio.h>

void writeListToFile(List* list, size_t elemSize, FILE* file);
List readFileAsList(size_t elemSize, FILE* file);
#endif
