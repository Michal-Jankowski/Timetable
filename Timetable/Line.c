#include "Line.h"
#include "DataBase.h"
#include<stdlib.h>
#include "debug.h"

// tworzeniee pustego elementu linii autobusowej
Line* createLine(unsigned number) {
	Line* l = MALLOC(sizeof(Line));
	l->number = number;
	initList(&l->busStops);
	return l;
}


// wyszukiwanie linii autobusowej za pomoc¹ liczby "number" ze stukrutry Line iteruj¹ca po ListElem
ListElem *findLineByNumber(List*list, unsigned number) {
	ListElem* e = list->head;
	while (e != NULL) {
		Line* l = (Line*)e->value;
		if (l->number == number)
			return e;
		e = e->next;
	}
	return NULL;
}
// dealokacja elementu linii autobusowej
void deallocLine(Line* s) {
	if (s == NULL)
		return;
	deallocList(&s->busStops);
	FREE(s);
}
// sczytywanie linii autobusowej
Line * readBusLineFromFile(FILE * file) {
	Line* line = (Line*)MALLOC(sizeof(Line));
	initList(&line->busStops);
	line->number = readInt(file);
	return line;
}
 //zapisywanie danych o linii autobusowej do pliku za pomoc¹ funkcji writeInt
void writeBusLineToFile(Line * line, FILE * file) {
	writeInt(line->number, file);
}
