#ifndef LIST_H
#define LIST_H

#include <stddef.h>
#include <stdbool.h>

struct _ListElem {
	struct _ListElem* prev;
	struct _ListElem* next;
	void* value;
};

typedef struct _ListElem ListElem;

typedef struct {
	ListElem* head;
	size_t size;
} List;



ListElem* createDefaultElem(void* value);
ListElem* createElem(void* value, ListElem* prev, ListElem* next);
ListElem* end(List* list);
void insertAfter(ListElem* e, void* value);
void insertBefore(ListElem* e, void* value);
void pushFront(List* list, void* value);
ListElem* pushBack(List* list, ListElem* last, void* value);
//void pushBack(List* list, void* value); NARAZIE NIE KORZYSTAMY
void deallocList(List* list);
ListElem* removeValue(List* list, void* value); //znajduje i usuwa z listy ale nie dealokuje, zwraca wskaznik
void removeAll(List* list, void* value);
ListElem* find(List* list, void* value); //znajduje w liscie i zwraca wskaznik
void initList(List* list);
void* removeElem(List* list, ListElem* elem);

#endif
