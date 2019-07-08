#include "DataBase.h"
#include "debug.h"

//odczytanie stringa z pliku
char * readString(FILE * file) {
	//odczytanie rozmiaru tablicy
	int size = readInt(file);
	//alokacja
	char* str = (char*)MALLOC(size);
	//wczytanie binarne string do tablicy
	fread(str, size, 1, file);
	return str;
}

//zapisanie string do pliku
void writeString(const char * str, FILE * file) {
	//uzyskanie rozmiaru
	int size = strlen(str) + 1;
	//zapisanie rozmiaru
	fwrite(&size, sizeof(int), 1, file);
	//zapisanie stringa
	fwrite(str, size, 1, file);
}

//odczytanie binarnie inta z pliku
int readInt(FILE * file) {
	int value;
	fread(&value, sizeof(int), 1, file);
	return value;
}

//zapisanie binarnie inta do pliku
void writeInt(int i, FILE * file) {
	fwrite(&i, sizeof(int), 1, file);
}

//utworzenie dynamicznie alokowanej kopii stringa
char * copyString(char const * s) {
	char* result = (char*)MALLOC(strlen(s) + 1);
	strcpy(result, s);
	return result;
}

//funckja inicjuj¹ca ca³y proces wczytywania bazy danych z pliku
bool readDataBaseFromFile(const char * filename, DataBase * dataBase) {
	FILE* file = fopen(filename, "rb");
	if (file == NULL)
		return false;
	initList(&dataBase->cities);
	//iloœæ miast
	int nCities = readInt(file);
	//wczytanie kolejnych miast i dodanie do listy
	for (int i = 0; i < nCities; ++i)
		pushFront(&dataBase->cities, readCityFromFile(file));
	return true;
}

//funckja inicjuj¹ca ca³y proces zapisywania bazy danych do pliku
void writeDataBaseToFile(const char * filename, DataBase * dataBase) {
	FILE* file = fopen(filename, "wb");
	if (file == NULL)
		return;
	//zapisanie iloœci maist
	writeInt(dataBase->cities.size, file);
	//iteracja po liœcie miast i zapisanie ich do pliku
	ListElem* cityElem = dataBase->cities.head;
	while (cityElem != NULL) {
		writeCityToFile((City*)cityElem->value, file);
		cityElem = cityElem->next;
	}
}
