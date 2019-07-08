#ifndef LINE_H
#define LINE_H

#include "List.h"
#include <stdio.h>

// sturktura odpowiedzialna za linie autobusowe przechowuj�ca liste przystank�w autobusowych oraz numer danej linii
typedef struct {
	unsigned number;
	List busStops;
} Line;
// funkcja tworz�ca linie autobusow�
Line* createLine(unsigned number);
// funkcja wyszukuj�ca linie autobusow� po liczbie
ListElem*findLineByNumber(List*list, unsigned number);
// funkcja dealokuj�ca linie autobusow�
void deallocLine(Line* s);
// funkcja sczytuj�ca linie autobusowe z pliku
Line* readBusLineFromFile(FILE* file);
// funkcja zapisuj�ca linie autobusowe do pliku
void writeBusLineToFile(Line* line, FILE* file);

#endif