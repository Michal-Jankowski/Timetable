#ifndef INTERFACE_H
#define INTERFACE_H
#include <stdbool.h>
#include "List.h"
#include "DataBase.h"
// funkcje boolowskie odpowiedzialne za sprawdzanie poprawnoœci wprowadzonych danych przez u¿ytkownia, np. czy dane miasto istnieje
bool streq(char const* s1, char const* s2);
bool validCity(ListElem* cityElem);
bool validLine(ListElem* lineElem);
bool validBusStop(ListElem* busElem);

void readLine(char* buffer);
// funkcje dodajace
void addBusLineInterface(DataBase* dataBase);
void addCityInterface(DataBase* dataBase);
void addBusStopInterface(DataBase* dataBase);
void addBusStoptoLineInterface(DataBase* dataBase);
// funkcje usuwajace
void deleteCityInterface(DataBase* dataBase);
void deleteBusStopInterface(DataBase* dataBase);
void deleteLineInterface(DataBase* dataBase);
// funckje wyswietlajace
void displayCityInterface(DataBase * dataBase);
void displayCityLine(Line* line);
void displayBusStopInterface(DataBase* dataBase);
void displayBusStop(BusStop* stop);
void displayBusLine(Line* line);
void displayBusLineInterface(DataBase* dataBase);
// funkcje modyfikujace
void modifyBusStopInterface(DataBase* dataBase);
void setScheduleInterface(DataBase* dataBase);
void displayTimetableInterface(DataBase* dataBase);
void displaySchedule(Schedule* schedule);
char* getInput(char* buf);


#endif