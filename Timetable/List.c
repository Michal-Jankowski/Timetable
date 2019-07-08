#include "List.h"
#include <stdlib.h>
#include "debug.h"

//alokacja pustego elementu listy
ListElem * createDefaultElem(void * value) {
	return createElem(value, NULL, NULL);
}

//alokacja elementu listy i przypisanie wartoœci pól
ListElem * createElem(void * value, ListElem * prev, ListElem * next) {
	ListElem* e = MALLOC(sizeof(ListElem));
	if (e == NULL)
		return NULL;
	e->prev = prev;
	e->next = next;
	e->value = value;
	return e;
}


//wstawienie nowego elementu z podan¹ wartoœci¹ za podanym lementem listy
void insertAfter(ListElem * e, void * value) {
	e->next = createElem(value, e, e->next);
}

//wstawienie nowego elementu z podan¹ wartoœci¹ przed podanym lementem listy
void insertBefore(ListElem * e, void * value) {
	e->prev = createElem(value, e->prev, e);
}

//wstawienie elementu z wartoœci¹ na pocz¹tek listy
void pushFront(List * list, void * value) {
	//lista pusta
	if (list->head == NULL)
		list->head = createDefaultElem(value);
	else {
		//nowy element staje siê g³ow¹ a g³owa przypiêta do nowego
		ListElem* e = createElem(value, NULL, list->head);
		list->head->prev = e;
		list->head = e;
	}
	++list->size;
}

//wstawienie elementu z wartoœci¹ na koniec listy znaj¹c ostatni element listy
ListElem * pushBack(List * list, ListElem * last, void * value) {
	if (list->head == NULL) {
		list->head = createElem(value, NULL, NULL);
		return list->head;
	}
	else {
		ListElem* e = createElem(value, last, NULL);
		last->next = e;
		return e;
	}
}


//dealokacja kolejno wszystkich elementów listy
void deallocList(List * list) {
	ListElem* e1 = list->head;
	ListElem* e2;
	while (e1 != NULL) {
		e2 = e1->next;
		FREE(e1);
		e1 = e2;
	}
}

//usuniêcie elementu który ma podan¹ wartoœæ
ListElem * removeValue(List * list, void * value) {
	ListElem* e = find(list, value);
	if (e == list->head) {
		list->head = e->next;
		list->head->prev = NULL;
	}
	else {
		e->prev->next = e->next;
	}
	e->prev = NULL;
	e->next = NULL;
	return e;
}

void removeAll(List * list, void * value) {
	if (list == NULL)
		return;
	if (list->head == NULL)
		return;
	while (list->head != NULL && list->head->value == value) {
		ListElem* next = list->head->next;
		FREE(list->head);
		list->head = next;
		--list->size;
	}
	if (list->head != NULL) {
		ListElem* e = list->head->next;
		while (e != NULL) {
			if (e->value == value) {
				ListElem* next = e->next;
				ListElem* prev = e->prev;
				FREE(e);
				prev->next = next;
				e = next;
			}
			else
				e = e->next;
		}
	}
}

//znalezienie elementu który ma podan¹ wartoœæ
ListElem * find(List * list, void * value) {
	ListElem* e = list->head;
	while (e != NULL) {
		if (e->value == value)
			return e;
		e = e->next;
	}
	return NULL;

	
}

//ustawienie pocz¹tkowych wartoœci pól struktury List
void initList(List * list) {
	list->head = NULL;
	list->size = 0;
}

//usuniêcie konkretnego elemnentu z listy i zwrócenie wartoœci któr¹ przechowywa³
void* removeElem(List * list, ListElem * elem) {
	if (elem == NULL)
		return NULL;
	if (list->head == NULL)
		return NULL;
	if (elem == list->head) {
		//zapamiêtanie elementu za g³ow¹ i wartoœci
		ListElem* after = list->head->next;
		void* value = list->head->value;
		//usuniêcie g³owy i oznaczenie kolejnego elementu jako g³owa
		FREE(list->head);
		list->head = after;
		--list->size;
		return value;
	}
	//zapamiêtanie elementu przed, po oraz wartoœci elementu usuwanego
	ListElem* after = elem->next;
	ListElem* before = elem->prev;
	void* value = elem->value;
	FREE(elem);
	//przypiêcie elementu przed do elementu po
	before->next = after;
	--list->size;
	return value;
}

////to samo co funkcja powy¿ej ale z dealokacj¹ wartoœci elementu listy który usuwamy
//void removeDeallocElem(List * list, ListElem * elem) {
//	if (elem == NULL)
//		return;
//	if (list->head == NULL)
//		return;
//	if (elem == list->head) {
//		ListElem* after = list->head->next;
//		FREE(list->head->value);
//		FREE(list->head);
//		list->head = after;
//		return;
//	}
//	ListElem* after = elem->next;
//	ListElem* before = elem->prev;
//
//	FREE(elem->value);
//	FREE(elem);
//	before->next = after;
//	return;
//}