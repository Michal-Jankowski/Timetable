#include"Interface.h"
#include <stdbool.h>
#include "debug.h"

#define BUFSIZE 128 // rozmair bufora
//poównanie stringów
bool streq(char const* s1, char const* s2) {
	return strcmp(s1, s2) == 0;
}

//pomocniczo sprawdzenie czy znalezione miasto jest NULL czy nie
bool validCity(ListElem* cityElem) {
	if (cityElem == NULL || cityElem->value == NULL) {
		printf("City with given name does not exist.\n");
		return false;
	}
	return true;
}

//pomocniczo sprawdzenie czy miasto o podanej nazwie nie isnieje w bazie
bool assertCityNotExists(List* cities, const char* name) {
	ListElem* cityElem = findCityByName(cities, name);
	if (cityElem != NULL) {
		printf("City with given name already exists.\n");
		return false;
	}
	return true;
}

//pomocniczo sprawdzenie czy znaleziona linia jest NULL czy nie
bool validLine(ListElem* lineElem) {
	if (lineElem == NULL || lineElem->value == NULL) {
		printf("Line with given name does not exist.\n");
		return false;
	}
	return true;
}

//pomocniczo sprawdzenie czy znaleziony przystanek jest NULL czy nie
bool validBusStop(ListElem* busElem) {
	if (busElem == NULL || busElem->value == NULL) {
		printf("BusStop with given name does not exist.\n");
		return false;
	}
	return true;
}
// sczytywanie liniie autobusowej (funkcja pomocnicza)
void readLine(char * buffer) {
	scanf_s("%[^\n]", buffer, BUFSIZE);
}

//interfejs dodawania linii do bazy
void addBusLineInterface(DataBase* dataBase) {
	printf("add busline >> ");
	printf("input: [city] [busline number]\n");
	char cityName[BUFSIZE] = { 0 };
	int busLineNumber;
	//wczytanie nazwy miasta i numeru linii
	if (scanf("%s %d", cityName, &busLineNumber) != 2) {
		printf("Invalid input.\n");
		return;
	}
	//zapewnienie ¿e miasto istnieje
	ListElem*cityElem  = findCityByName(&dataBase->cities, cityName);
	if (!validCity(cityElem))
		return;
	//dodanie linii do miasta
	addLine((City*)cityElem->value, busLineNumber);
	printf("done.\n");
}

//interfejs dodawania przystanku do linii
void addBusStoptoLineInterface(DataBase* dataBase) {
	printf("add busStop to Line >> ");
	printf("input: [city] [busstop name] [busline number]\n");
	char cityName[BUFSIZE] = { 0 }; 
	char busStopName[BUFSIZE] = { 0 };
	int busLineNumber;
	//wczytanie nazwy miasta i numeru linii
	if (scanf("%s %s %d", cityName,busStopName, &busLineNumber) != 3) {
		printf("Invalid input.\n");
		return;
	} 
	//zapewnienie ¿e miasto istnieje
	ListElem* cityElem = findCityByName(&dataBase->cities, cityName);
	if (!validCity(cityElem))
		return;
	City* city = (City*)cityElem->value;

	//zapewnienie ¿e linia istnieje
	ListElem* busLineElem = findLineByNumber(&city->busLines, busLineNumber);
	if (!validLine(busLineElem))
		return;
	Line* line = (Line*)busLineElem->value;

	//zapewnienie ¿e przystanek istnieje
	ListElem* BusStopElem = findBusStopByName(&city->busStops, busStopName);
	if (!validBusStop(busLineElem))
		return;
	BusStop* stop = NULL;
	if (BusStopElem == NULL) {
		stop = addBusStop(city, busStopName);
	}
	else {
		stop = (BusStop*)BusStopElem->value;
	}
	Schedule* sch = createSchedule(line);
	pushFront(&stop->schedules, sch);

	printf("done.\n");
}
//interfejs dodawania miasta
void addCityInterface(DataBase* dataBase) {
	printf("add city >> ");
	printf("input: [city]\n");
	char cityName[BUFSIZE] = { 0 };
	//wczytanie nazwy miasta
	if (scanf("%s", cityName) != 1) {
		printf("Invalid input.\n");
		return;
	}
	//zapewnienie ¿e miasto jeszcze nie istnieje i dodanie do bazy
	if (assertCityNotExists(&dataBase->cities, cityName))
		pushFront(&dataBase->cities, createCity(cityName));
	   printf("done.\n");
}

//interfejs dodawania przystanku
void addBusStopInterface(DataBase* dataBase) {
	printf("add Busstop >> ");
	printf("input: [city] [busstop name]\n");
	char cityName[BUFSIZE] = { 0 };
	char busStopName[BUFSIZE] = { 0 };
	//wczytanie nazwy miasta i nazwy przystanku
	if (scanf("%s %s", cityName, busStopName) != 2) {
		printf("Invalid input.\n");
		return;
	}
	//zapewnienie ¿e miasto istnieje
	ListElem* cityElem = findCityByName(&dataBase->cities, cityName);
	if (!validCity(cityElem))
		return;
	City* city = (City*)cityElem->value;
	//zapewnienie ¿e taki przystanek w podanym mieœcie jeszcze nie istnieje i dodanie do bazy
	ListElem* busStopElem = findBusStopByName(&city->busStops, busStopName);
	if (busStopElem == NULL) {
		addBusStop(city, busStopName);
		printf("done.\n");
	}
}
// funkcja odpowiedzialna za uswanie miasta podanego przez uzytkownika
void deleteCityInterface(DataBase* dataBase) {
	printf("delete city >> "); 
	printf("input: [city]\n");
	char cityName[BUFSIZE] = { 0 };
	if (scanf("%s", cityName) != 1) {
		printf("Invalid input.\n");
		return;
	}
	//zapewnienie ¿e miasto istnieje
	ListElem* cityElem = findCityByName(&dataBase->cities, cityName);
	if (!validCity(cityElem))
		return;
	//usuniêcie z listy i dealokacja
	City* city = removeElem(&dataBase->cities, cityElem);
	deallocCity(city);
	printf("done.\n");
}

//usuwanie przystanku
void deleteBusStopInterface(DataBase* dataBase) { 
	printf("delete bus stop >> ");
	printf("input: [city] [busstop name]\n");
	char cityName[BUFSIZE] = { 0 };
	char busStopname[BUFSIZE] = { 0 };
	if (scanf("%s %s", cityName, busStopname) != 2) {
		printf("Invalid input.\n");
		return;
	}//zapewnienie ¿e miasto istnieje
	ListElem* cityElem = findCityByName(&dataBase->cities, cityName);
	if (!validCity(cityElem))
		return;
	City* city = (City*)cityElem->value;
	//zapewnienie ¿e przystanek istnieje
	ListElem* busElem = findBusStopByName(&city->busStops, busStopname);
	if (!validBusStop(busElem))
		return;
	//usuniêcie z listy i dealokacja
	BusStop* stop = removeElem(&city->busStops, busElem);
	removeReferences(stop);
	deallocBusStop(stop);
	printf("done.\n");
}

// usuwanie linii autobusowej
void deleteLineInterface(DataBase* dataBase) { 
	printf("delete busline >> "); 
	printf("input: [city] [busline number]\n");
	char cityName[BUFSIZE] = { 0 };
	int busLineNumber;
	//wczytanie nazwy miasta i numeru linii
	if (scanf("%s %d", cityName, &busLineNumber) != 2) {
		printf("Invalid input.\n");
		return;
	}
	//zapewnienie ¿e miasto istnieje
	ListElem* cityElem = findCityByName(&dataBase->cities, cityName);
	if (!validCity(cityElem))
		return;
	City* city = (City*)cityElem->value;

	ListElem* lineElem = findLineByNumber(&city->busLines, busLineNumber);
	if (!validLine(lineElem))
		return;

	Line* line = removeElem(&city->busLines, lineElem);
	deallocLine(line);

	printf("done.\n");
}

//interfejs wyœwietlania ca³ych danych o mieœcie
void displayCityInterface(DataBase* dataBase) {
	printf("show city >> ");
	printf("input: [city]\n");
	char cityName[BUFSIZE] = { 0 };
	//wczytanie nazwy miasta
	if (scanf("%s", cityName) != 1) {
		printf("Invalid input.\n");
		return;
	}
	//zapewnienie ze miasto istnieje
	ListElem*cityElem = findCityByName(&dataBase->cities, cityName);
	if (!validCity(cityElem))
		return;
	//iteracja po liniach i wyœwietlanie danych o linii
	ListElem* lineElem = ((City*)cityElem->value)->busLines.head;
	while (lineElem != NULL) {
		Line* line = (Line*)lineElem->value;
		displayCityLine(line);
		lineElem = lineElem->next;
	}
}

// wyszukiwanie miast poprez iteracje po elementach listy (funkcja pomocnicza do interefejsu miasta)
void displayCityLine(Line* line) {
	if (line == NULL)
		return;
	printf("Line %d:\n", line->number);
	//iteracja po przystankach linii i wyœwietlenie nazw
	ListElem* busstopElem = line->busStops.head;
	while (busstopElem != NULL) {
		BusStop* stop = busstopElem->value;
		if (stop == NULL)
			printf("NULL\n");
		else
			printf("%s\n", stop->name);
		busstopElem = busstopElem->next;
	}
}
// wyszukiwanie przystanków autbuoswych poprez iteracje po elementach listy (funkcja pomocnicza do interefejsu przystanków)

void displayBusStop(BusStop* stop) {
	if (stop == NULL)
		return;
	//iteracja po rozk³adach i wyœwietlenie ich kolejno
	ListElem* scheduleElem = stop->schedules.head;
	while (scheduleElem != NULL) {
		Schedule* schedule = scheduleElem->value;
		if (schedule == NULL)
			printf("NULL\n");
		else
			displaySchedule(schedule);
		scheduleElem = scheduleElem->next;
	}
}
// wysszukiwanie linii autbuoswych poprez iteracje po elementach listy (funkcja pomocnicza do interefejsu linii)
void displayBusLine(Line* line) {
	if (line == NULL)
		return;
	printf("Line %d:\n", line->number);
	ListElem* buslineElem = line->busStops.head;
	while (buslineElem != NULL) {
		Line* lines = buslineElem->value;
		if (lines == NULL)
			printf("NULL\n");
		else
			printf("%d\n", lines->number);
		buslineElem = buslineElem->next;
	}
}
// interfejs odpowiedzialny za wyspisywanie linii autobusowych
void displayBusLineInterface(DataBase* dataBase) {
	char cityName[BUFSIZE] = { 0 };
	int busLineNumber;
	printf("show busline >> ");
	printf("input: [city] [busline number]\n");
	if (scanf("%s %d", cityName, &busLineNumber) != 2) {
		printf("Invalid input.\n");
		return;
	}
	//zapewnienie ze miasto istnieje
	ListElem*cityElem = findCityByName(&dataBase->cities, cityName);
	if (!validCity(cityElem))
		return;
	City* city = (City*)cityElem->value;

	ListElem* BusLineElem = findLineByNumber(&city->busLines, busLineNumber);
	if (!validLine(BusLineElem))
		return;
	ListElem* lineElem = ((City*)cityElem->value)->busLines.head;
		Line* line = (Line*)lineElem->value;
		displayBusLine(line);
}
// interfejs wyœwietlaj¹cy danych przez uzytkownika przystanek autobusowy
void displayBusStopInterface(DataBase* dataBase) 
{
	char cityName[BUFSIZE] = { 0 };
	char busStopname[BUFSIZE] = { 0 };
	printf("show busstop >> ");
	printf("input: [city] [busstop name]\n");
	if (scanf("%s %s", cityName, busStopname) != 2) {
		printf("Invalid input.\n");
		return;
	}
	//zapewnienie ze miasto istnieje
	ListElem*cityElem = findCityByName(&dataBase->cities, cityName);
	if (!validCity(cityElem))
		return;
	City* city = (City*)cityElem->value;
	//zapewnienie ¿e przystanek istnieje
	ListElem* busElem = findBusStopByName(&city->busStops, busStopname);
	if (!validBusStop(busElem))
		return;
	ListElem* lineElem = ((City*)cityElem->value)->busStops.head;
	while (lineElem != NULL) {
		BusStop* stop = (BusStop*)lineElem->value;
		displayBusStop(stop);
		lineElem = lineElem->next;


		
	}
}
// interfejs umo¿liwiaj¹cy modyfikacje przstanku autobusowego przez u¿ytkownika maj¹ca na celu zamianê nazwy danego przystanku
void modifyBusStopInterface(DataBase* dataBase) {
	printf("modify busstop >> ");
	printf("input: [city] [busstop name]\n");
	char cityName[BUFSIZE] = { 0 };
	char busStopName[BUFSIZE] = { 0 };
	if (scanf("%s %s", cityName, busStopName) != 2) {
		printf("Invalid input.\n");
		return;
	}
	// sprawdzanie czy miasto istnieje
	ListElem* cityElem = findCityByName(&dataBase->cities, cityName);
	if (!validCity(cityElem))
		return;
	City* city = (City*)cityElem->value;
	// sprawdzanie czy przystanek autobusowy istnieje
	ListElem* LineElem = findBusStopByName(&city->busStops, busStopName);
	if (LineElem == NULL) {
		return;
	}
	BusStop* stop = (BusStop*)LineElem->value;
	printf("new busstop name:\n");
	readLine(busStopName);
	FREE(stop->name);
	stop->name = copyString(busStopName);
	printf("done.\n");

}

//wyœwietlenie rozk³adów godzin odjazdów
void displayTimetableInterface(DataBase* dataBase) {
	char cityName[BUFSIZE] = { 0 };
	char busStopname[BUFSIZE] = { 0 };
	int busLineNumber;
	printf("input: [city] [busstop name] [busline number]\n");
	if (scanf("%s %s %d", cityName, busStopname, &busLineNumber) != 3) {
		printf("Invalid input.\n");
		return;
	}//zapewnienie ¿e miasto istnieje
	ListElem* cityElem = findCityByName(&dataBase->cities, cityName);
	if (!validCity(cityElem))
		return;
	City* city = (City*)cityElem->value;
	//zapewnienie ¿e przystanek istnieje
	ListElem* busElem = findBusStopByName(&city->busStops, busStopname);
	BusStop* stop = (BusStop*)busElem->value;
	if (!validBusStop(busElem))
		return;
	ListElem* schElem = findScheduleByLine(&stop->schedules, busLineNumber);
	if (schElem == NULL) {
		printf("Schedule for given line on given busstop does not exist\n");
		return;
	}
	Schedule* schedule = (Schedule*)schElem->value;

	displaySchedule(schedule);

}

//wyœwietlenie rozk³adów linii
void displaySchedule(Schedule* schedule) {
	printf("%d:\n", schedule->line->number);
	printf("weekday:   ");
	displayTimetable(&schedule->weekday);
	printf("\n");
	printf("saturday:  ");
	displayTimetable(&schedule->saturday);
	printf("\n");
	printf("sunday:    ");
	displayTimetable(&schedule->sunday);
	printf("\n");
}

//pomocniczo pobranie stringa
char* getInput(char* buf) {
	scanf("%s", buf);
	return buf;
}
// funkcja boolowska maj¹ca na celu sprawdzenia poprawnoœci wprowadzonych godzin przez u¿ytkownika
bool parseTime(char const* str, Time* t) {
	int hour;
	int minutes;
	if (sscanf(str, "%2d:%2d", &hour , &minutes) != 2) {
		printf("Invalid time format\n");
		return false;
	}
     if (hour > 24 || minutes > 60) {
		printf("Invalid time format\n");
		return false;
	}
	t->hour = (byte)hour;
	t->minutes = (byte)minutes;
	return true;
}
// funkcja odpowiedzialna za przypisanie godziny w rozkladach jazdy w zale¿noœci od podzia³u tygodnia 
void setScheduleInterface(DataBase* dataBase) {
	char cityName[BUFSIZE] = { 0 };
	char busStopname[BUFSIZE] = { 0 };
	int busLineNumber;
	char day[10] = { 0 };
	char timesBuffer[1024] = { 0 };
	printf("input: [city] [busstop name] [busline number] [day]\n");
	if (scanf("%s %s %d %s", cityName, busStopname, &busLineNumber, day) != 4) {
		printf("Invalid input.\n");
		return;
	}//zapewnienie ¿e miasto istnieje
	ListElem* cityElem = findCityByName(&dataBase->cities, cityName);
	if (!validCity(cityElem))
		return;
	City* city = (City*)cityElem->value;
	//zapewnienie ¿e przystanek istnieje
	ListElem* busElem = findBusStopByName(&city->busStops, busStopname);
	BusStop* stop = (BusStop*)busElem->value;
	if (!validBusStop(busElem))
		return;
	ListElem* lineElem = findLineByNumber(&city->busLines, busLineNumber);
	if (!validLine(lineElem))
		return;
	Line* line = (Line*)lineElem->value;
	
	//rozmiar stringa
	int size;
	//ilosc godzin
	int nTimes;

	//bufor na typ rozkladu
	
	Schedule* schedule = NULL;
	ListElem* schElem = findScheduleByLine(&stop->schedules, busLineNumber);
	bool isNew = true;
	if (schElem != NULL) {
		schedule = (Schedule*)schElem->value;
		isNew = false;
	}
	
	//wskaznik na timetable w utworznym schedule w zaleznoœci od typu rozkladu weekday/saturday/sunday
	Timetable* table;
	if (streq(day, "weekday")) {
		if (schedule == NULL)
			schedule = createSchedule(line);
		table = &schedule->weekday;
	}
	else if (streq(day, "saturday")) {
		if (schedule == NULL)
			schedule = createSchedule(line);
		table = &schedule->saturday;
	}
	else if (streq(day, "sunday")) {
		if (schedule == NULL)
			schedule = createSchedule(line);
		table = &schedule->sunday;
	}
	else {
		printf("Invalid schedule type\n");
		return;
	}

	schedule->line = line;

	fseek(stdin, 0, SEEK_END);
	//wczytujemy wszystkie time w jednej linii w formacie xx:xx oddzielone spacjami
	scanf("%[^\n]", timesBuffer);
	fseek(stdin, 0, SEEK_END);
	size = strlen(timesBuffer);
	//kazdy time oprocz ostatniego zajmuje 6 znakow
	if (size % 6 != 5) {
		printf("Invalid format\n");
		if (isNew)
			FREE(schedule);
		return;
	}
	// je¿eli uda siê wprowadziæ dane
	nTimes = size / 6 + 1;
	table->size = nTimes;
	if (table->data != NULL)
		FREE(table->data);
	table->data = MALLOC(nTimes * sizeof(Time));
	// iteracja po iloœci wprowadonych godzin, sprawdzanie ich poprawnoœci 
	for (int i = 0; i < nTimes; ++i) {
		if (!parseTime(timesBuffer + i * 6, &table->data[i])) {
			FREE(table->data);
			table->data = 0;
			if (isNew)
				FREE(schedule);
			return;
		}
	}
	
	if (!isNew) // je¿eli ju¿ nie wyst¹pi³
		pushFront(&stop->schedules, schedule);
} 