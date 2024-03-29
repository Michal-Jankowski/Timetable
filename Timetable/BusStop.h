#ifndef BUSTOP_H
#define BUSTOP_H 

#include <stddef.h>
#include "Line.h"
#include <string.h>
#include <stdbool.h>
#include <stdio.h>

typedef unsigned char byte;
//alias nazwy dla City
typedef struct _City City;
//struktura Time odpowiedzialna za ustawianie godziny odjazdu w rozkladach jazdy "schedule"
typedef struct {
	byte hour;
	byte minutes;
} Time;
// sturktura Timetable przechowująca inforamcje odwoalnie do sturktury Time oraz swoj rozmiar wykorzystywana do okręślenia danego dnia np. dnia pracy
typedef struct {
	Time* data;
	size_t size;
} Timetable;
// sturktura przechowująca odwołanie do istniejącej linii oraz podzielonych dni tygodnia
typedef struct {
	Line* line; //odwołanie do istniejacej juz linii
	Timetable weekday;
	Timetable saturday;
	Timetable sunday;
} Schedule;
// struktura służaca do przechowywania informacji o przystankach autobusowych, ich nazwie id oraz odowałań do rozkładów jazdy
typedef struct {
	char* name;
	unsigned id;
	List schedules;
} BusStop;

//funkcje wyszukujace przystanki i rozklad jazdy
ListElem* findBusStopByName(List* list, const char* name);
ListElem*findBusStopById(List* list, unsigned id);
ListElem* findScheduleByLine(List* list, unsigned n);
//funkcje tworzące przystanki i rozklad jazdy
BusStop* createBusStop(const char* name, unsigned id);
Schedule* createSchedule(Line* line);
void initTimeTable(Timetable* t);
//funkcje dealokujące rozklad i przystanki
void deallocBusStop(BusStop* s);
void deallocSchedule(Schedule* t);
//funkcje wyswietlające godziny wykorzystywane w rozkladzie jazdy
void displayTimetable(Timetable* t);
void displayTime(Time t);
// funkcje sczytujące z pliku binarnego przystanki i rozklad jazdy
Timetable readTimetableFromFile(FILE* file);
Schedule* readScheduleFromFile(FILE* file);
BusStop* readBusStopFromFile(FILE* file);
void readSchedules(City* city, FILE* file);
// funkcje zapisujące do pliku binarnego przystanki i rozklad jazdy
void writeScheduleToFile(Schedule* schedule, FILE* file);
void writeTimetableToFile(Timetable* table, FILE* file);
void writeBusStopToFile(BusStop* stop, FILE* file);
void writeSchedules(City* city, FILE* file);

// funkcja wykorzystywana w "Busstop" w celu usunięcia odwołań przystanków
void removeReferences(BusStop* stop);

#endif
