#include "debug.h"
#include <stdio.h>

// statyczne zmienne wcelu zliacznia alkoacji i dealokacji
static int deallocations = 0;
static int allocations = 0;
// funkcja przy kazdej dealokacji zwiêksza liczbê elementów deallocations oraz wypisuje ich aktualn¹ liczbê
void freeDebug(void * ptr, char const* func) {
	free(ptr);
	++deallocations;
	printf("free in %s: %d:%d\n", func, allocations, deallocations);
}
//funkcja przy kazdej alokacji zwiêksza liczbê elementów allocations oraz wypisuje ich aktualn¹ liczbê
void* mallocDebug(size_t size, char const* func) {
	void* ptr = malloc(size);
	if (ptr != NULL) {
		++allocations;
		printf("malloc in %s: %d:%d\n", func, allocations, deallocations);
	}
	return ptr;
}
