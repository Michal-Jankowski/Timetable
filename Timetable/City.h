#ifndef CITY_H
#define CITY_H

#include "BusStop.h"
#include "Line.h"
#include "List.h"
//g��wna struktura miast przechowuj�ca odwo�ania do listy przystank�w oraz linii autobusowych i nazw� danego miasta
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
// sczytywanie zawarto�ci pliku binarnego z miast
City* readCityFromFile(FILE* file);
// zapisywanie miast oraz przystank�w autobusowych do miast
void writeCityToFile(City* city, FILE* file);
#endif

