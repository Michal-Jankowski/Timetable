#include "File.h"
#include <stdlib.h>
#include "debug.h"
#include "DetectMemoryLeaks.h"
void writeListToFile(List* list, size_t elemSize, FILE* file) {
	ListElem* e = list->head; //iterator po liscie
	while (e != NULL) { //dopoki nie doszliœmy do konca listy
		fwrite(e->value, elemSize, 1, file); //
		e = e->next; // // 5     1   2   3  4  5
	}
}

List readFileAsList(size_t elemSize, FILE* file) {
	List list; //tworzymy strukturê listy
	initList(&list); //inicjalizujemy (NULLE, zera)
	ListElem* last = NULL; //tworzymy iterator po liœcie
	void* value = MALLOC(elemSize); //alokujemy 
	if (fread(value, elemSize, 1, file) == 1) {
		ListElem* e = createElem(value, last, NULL);
		last = e;
		list.head = e;
		value = MALLOC(elemSize);
	}
	else {
		FREE(value);
		return list;
	}

	while (fread(value, elemSize, 1, file) == 1) {
		ListElem* e = createElem(value, last, NULL);
		last->next = e;
		last = e;
		value = MALLOC(elemSize);
	}
	FREE(value);
	return list;
}



List read(size_t elemSize, FILE* file) {
	List list; //tworzymy strukturê listy
	initList(&list); //inicjalizujemy (NULLE, zera)
	ListElem* last = NULL; //tworzymy iterator po liœcie
	void* value = MALLOC(elemSize); //alokujemy 
	if (fread(value, elemSize, 1, file) == 1) {
		ListElem* e = createElem(value, last, NULL);
		last = e;
		list.head = e;
		value = MALLOC(elemSize);
	}
	else {
		FREE(value);
		return list;
	}

	while (fread(value, elemSize, 1, file) == 1) {
		ListElem* e = createElem(value, last, NULL);
		last->next = e;
		last = e;
		value = MALLOC(elemSize);
	}
	FREE(value);
	return list;
}