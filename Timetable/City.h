#ifndef CITY_H
#define CITY_H

#include "BusStop.h"
#include "Line.h"
#include "List.h"
//g³ówna struktura miast przechowuj¹ca odwo³ania do listy przystanków oraz linii autobusowych i nazwê danego miasta
struct _City {
	char* name;
	List busStops;
	List busLines;
};
//alias nazwy City
typedef struct _City City;

// dodawanie przystankow autobusowych oraz linii autobusowych
BusStop* addBusStop(City* city, const char* name);
Line*addLine(City* city, unsigned number); 
// wyszukiwanie miasta po nazwie
ListElem* findCityByName(List* cities, const char* name);
// tworzenie miasta
City* createCity(char* name);
// dealokowanie miasta
void deallocCity(City* s);
// sczytywanie zawartoœci pliku binarnego z miast
City* readCityFromFile(FILE* file);
// zapisywanie miast oraz przystanków autobusowych do miast
void writeCityToFile(City* city, FILE* file);
#endif

