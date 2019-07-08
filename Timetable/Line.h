#ifndef LINE_H
#define LINE_H

#include "List.h"
#include <stdio.h>

// sturktura odpowiedzialna za linie autobusowe przechowuj¹ca liste przystanków autobusowych oraz numer danej linii
typedef struct {
	unsigned number;
	List busStops;
} Line;
// funkcja tworz¹ca linie autobusow¹
Line* createLine(unsigned number);
// funkcja wyszukuj¹ca linie autobusow¹ po liczbie
ListElem*findLineByNumber(List*list, unsigned number);
// funkcja dealokuj¹ca linie autobusow¹
void deallocLine(Line* s);
// funkcja sczytuj¹ca linie autobusowe z pliku
Line* readBusLineFromFile(FILE* file);
// funkcja zapisuj¹ca linie autobusowe do pliku
void writeBusLineToFile(Line* line, FILE* file);

#endif