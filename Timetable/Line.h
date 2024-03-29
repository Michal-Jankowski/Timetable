#ifndef LINE_H
#define LINE_H

#include "List.h"
#include <stdio.h>

// sturktura odpowiedzialna za linie autobusowe przechowująca liste przystanków autobusowych oraz numer danej linii
typedef struct {
	unsigned number;
	List busStops;
} Line;
// funkcja tworząca linie autobusową
Line* createLine(unsigned number);
// funkcja wyszukująca linie autobusową po liczbie
ListElem*findLineByNumber(List*list, unsigned number);
// funkcja dealokująca linie autobusową
void deallocLine(Line* s);
// funkcja sczytująca linie autobusowe z pliku
Line* readBusLineFromFile(FILE* file);
// funkcja zapisująca linie autobusowe do pliku
void writeBusLineToFile(Line* line, FILE* file);

#endif