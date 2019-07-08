#ifndef DATABASE_H
#define DATABASE_H

#include "City.h"
#include "BusStop.h"
#include "Line.h"
#include "List.h"
// struktura przechowuj�ca list� miast, baza danych programu
typedef struct {
	List cities;
} DataBase;
// sczytywanie stringa
char* readString(FILE* file);
// kopiowanie stringa
char* copyString(char const* s);
// zapisywanie stringa do pliku binarnego
void writeString(const char* str, FILE* file);
// sczytywanie int�w
int readInt(FILE* file);
// zapisywanie int�w do pliku binarnego
void writeInt(int i, FILE* file);
// funckja inicjuj�ca ca�y proces wczytywania bazy danych z pliku
bool readDataBaseFromFile(const char* filename, DataBase* dataBase);
// funckja inicjuj�ca ca�y proces zapisywania bazy danych do pliku
void writeDataBaseToFile(const char* filename, DataBase* dataBase);

#endif