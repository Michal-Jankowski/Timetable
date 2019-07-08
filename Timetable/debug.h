#ifndef DEBUG_H
#define DEBUG_H

#include <stdlib.h>
// funckje odpowiedzialne za zliczanie ilo�ci alokacji i dealkoacji pami�cie
void freeDebug(void* ptr, char const* func);
void* mallocDebug(size_t size, char const* func);
// w��czone zliczanie gdy debug 1 wy��czone przy debug 0
#define DEBUG 1
// warunek dzia�ania
#if DEBUG
#define FREE(ptr) { if (ptr != NULL) freeDebug(ptr, __FUNCTION__); }
#define MALLOC(ptr) mallocDebug(ptr, __FUNCTION__)
#else // warunek niedzia�ania
#define FREE(ptr) free(ptr)
#define MALLOC(ptr) malloc(ptr)
#endif

#endif