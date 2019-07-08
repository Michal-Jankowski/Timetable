#include "City.h"
#include <stdlib.h>
#include "DataBase.h"
#include "debug.h"


// dodanie przystanku autobusowego
BusStop* addBusStop(City* city, const char* name) {
	BusStop* s = createBusStop(name, city->busStops.size);
	pushFront(&city->busStops, s);
	return s;
}



// utworzenie  danego miasta 
City* createCity(char* name) {
	City* s = MALLOC(sizeof(City));
	s->name = copyString(name);
	initList(&s->busLines);
	initList(&s->busStops);
	return s;
}
// utworzenie linii autobusowej z wykorzystaniem funkcji pushfront
Line*addLine(City* city, unsigned number) {
	Line* line = createLine(number);
	pushFront(&city->busLines, line);
	return line;
}
// funckja dealokuj¹ca przystanek autobusowy
void deallocBusStopList(List* list) {
	ListElem* e1 = list->head;
	ListElem* e2;
	while (e1 != NULL) {
		e2 = e1->next;
		deallocBusStop((BusStop*)e1->value);
		FREE(e1);
		e1 = e2;
	}
}
// funkcja dealokuj¹ca linie autobusow¹
void deallocBusLinesList(List* list) {
	ListElem* e1 = list->head;
	ListElem* e2;
	while (e1 != NULL) {
		e2 = e1->next;
		deallocLine((Line*)e1->value);
		FREE(e1);
		e1 = e2;
	}
}

// dealokacja  miasta
void deallocCity(City* s) {
	if (s == NULL)
		return;
	FREE(s->name);
	deallocBusLinesList(&s->busLines);
	deallocBusStopList(&s->busStops);
	FREE(s);

}

// odczytywanie z pliku nazwy miasta z wykorzystaniem funkcji pushfront readschedule oraz initList i readString
City * readCityFromFile(FILE * file) {
	City* city = (City*)MALLOC(sizeof(City));
	city->name = readString(file);
	initList(&city->busStops);
	int nBusStops = readInt(file);
	for (int i = 0; i < nBusStops; ++i)
		pushFront(&city->busStops, readBusStopFromFile(file));
	initList(&city->busLines);
	int nBusLines = readInt(file);
	for (int i = 0; i < nBusLines; ++i)
		pushFront(&city->busLines, readBusLineFromFile(file));
	readSchedules(city, file);
	return city;
}
// zapisywanie danych o mieœcie do pliku
void writeCityToFile(City * city, FILE * file) {
	writeString(city->name, file);
	writeInt(city->busStops.size, file);
	ListElem* busStopElem = city->busStops.head;
	while (busStopElem != NULL) {
		writeBusStopToFile((BusStop*)busStopElem->value, file);
		busStopElem = busStopElem->next;
	}
	writeInt(city->busLines.size, file);
	ListElem* lineElem = city->busLines.head;
	while (lineElem != NULL) {
		writeBusLineToFile((Line*)lineElem->value, file);
		lineElem = lineElem->next;
	}
	writeSchedules(city, file);
}
// odczytywanie z pliku danych o przystankach autobusowych
//void readLineBusStopsFromFile(City* city, Line * line, FILE * file) {
//	int size = readInt(file);
//	ListElem* last = NULL;
//	initList(&line->busStops);
//	for (int i = 0; i < size; ++i) {
//		int busStopID = readInt(file);
//		BusStop* stop = findBusStopById(&city->busStops, busStopID);
//		last = pushBack(&line->busStops, last, stop);
//	}
//}

//zapis lini autobusowych do pliku binarnego
void writeLineBusStopsFromFile(Line * line, FILE * file) {
	writeInt(line->busStops.size, file);
	ListElem* stopElem = line->busStops.head;
	while (stopElem != NULL) {
		writeInt(((BusStop*)stopElem->value)->id, file);
		stopElem = stopElem->next;
	}
}


// znalezienie miasta za pomoc¹ nazwy "name" w liœcie miast
ListElem* findCityByName(List* cities, const char* name) {
	ListElem* e = cities->head;
	while (e != NULL) {
		City* city = (City*)e->value;
		if (strcmp(city->name, name) == 0)
			return e;
		e = e->next;
	}
	return NULL;
}

// zapisywanie danych o mieœcie do pliku
//void writeCityToFile(City * city, FILE * file) {
//	writeString(city->name, file);
//	writeInt(city->busStops.size, file);
//	ListElem* busStopElem = city->busStops.head;
//	while (busStopElem != NULL) {
//		writeBusStopToFile((BusStop*)busStopElem->value, file);
//		busStopElem = busStopElem->next;
//	}
//	writeInt(city->busLines.size, file);
//	ListElem* lineElem = city->busLines.head;
//	while (lineElem != NULL) {
//		writeBusLineToFile((Line*)lineElem->value, file);
//		lineElem = lineElem->next;
//	}
//	writeSchedules(city, file);
//}


