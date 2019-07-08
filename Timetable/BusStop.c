#include "BusStop.h"
#include "DataBase.h"
#include "debug.h"

//funckja alokuje dynamicznie pami�� na instancj� struktury BusStop i inicjalizuje warto�ci p�l
BusStop* createBusStop(const char* name, unsigned id) {
	BusStop* s = MALLOC(sizeof(BusStop));
	s->id = id;
	s->name = copyString(name);
	initList(&s->schedules);
	return s;
}

//dealokacja instancji BusStop z pe�n� dealokacj� element�w listy
void deallocBusStop(BusStop* s) {
	if (s == NULL)
		return;
	FREE(s->name);
	ListElem* e1 = s->schedules.head;
	ListElem* e2;
	while (e1 != NULL) {
		e2 = e1->next;
		deallocSchedule((Schedule*)e1->value);
		FREE(e1);
		e1 = e2;
	}
	FREE(s);
}

Schedule * createSchedule(Line * line) {
	Schedule* s = MALLOC(sizeof(Schedule));
	s->line = line;
	initTimeTable(&s->weekday);
	initTimeTable(&s->saturday);
	initTimeTable(&s->sunday);
	return s;
}
void deallocSchedule(Schedule* t) {
	if (t == NULL)
		return;
	FREE(t->weekday.data);
	FREE(t->saturday.data);
	FREE(t->sunday.data);
	FREE(t);
}

ListElem * findScheduleByLine(List * list, unsigned n) {
	ListElem* e = list->head;
	while (e != NULL) {
		Schedule* s = (Schedule*)e->value;
		if (s->line->number == n)
			return e;
		e = e->next;
	}
	return NULL;
}

void displayTimetable(Timetable * t) {
	for (unsigned i = 0; i < t->size; ++i)
		displayTime(t->data[i]);
}

void initTimeTable(Timetable * t) {
	t->data = NULL;
	t->size = 0;
}

void displayTime(Time t) {
	int h = t.hour;
	int m = t.minutes;
	printf("%.2d:%.2d ", h, m);
}

//wczytanie rozk�adu godzin odjazd�w z pliku i zwr�cenie go w postaci struktury Timetable
Timetable readTimetableFromFile(FILE * file) {
	Timetable a;
	a.size = readInt(file);
	if (a.size == 0)
		a.data = NULL;
	else {
		a.data = MALLOC(a.size * sizeof(Time));
		fread(a.data, sizeof(Time), a.size, file);
	}
	return a;
}

//wczytanie z pliku rozk�ad�w dla linii kolejno na dni powszednie, soboty, niedziele 
//i zwr�cenie ich w postaci dynamicznie zaalokowanej struktury Schedule
Schedule * readScheduleFromFile(FILE * file) {
	Schedule* schedule = (Schedule*)MALLOC(sizeof(Schedule));
	schedule->weekday = readTimetableFromFile(file);
	schedule->saturday = readTimetableFromFile(file);
	schedule->sunday = readTimetableFromFile(file);
	return schedule;
}

//zapisanie Schedule do podanego pliku
void writeScheduleToFile(Schedule * schedule, FILE * file) {
	writeInt(schedule->line->number, file); // numer linii
	writeTimetableToFile(&schedule->weekday, file);
	writeTimetableToFile(&schedule->saturday, file);
	writeTimetableToFile(&schedule->sunday, file);
}

//zapisanie do pliku rozk�adu odjazd�w: kolejno rozmiar tablicy i binarnie ca�a tablica z czasami odjazd�w
void writeTimetableToFile(Timetable * table, FILE * file) {
	writeInt(table->size, file);
	fwrite(table->data, sizeof(Time), table->size, file);
}

//miasta
//wczytujemy przystanki - dodajemy do listy struktury przystankow z nazwami bez powi�za�
//linie
//	nazwa
//	lista przystankow
//rozk�ady
//	nr linii
//	numery przystankow
//		

//zaalokowanie dynamicznie struktury BusStop i wczytanie danych o przystanku z pliku
BusStop * readBusStopFromFile(FILE * file) {
	BusStop* stop = (BusStop*)MALLOC(sizeof(BusStop));
	stop->id = readInt(file);
	stop->name = readString(file);

	initList(&stop->schedules);
	/*
	fread(&length, sizeof(unsigned), 1, file);

	if (length > 0) {
	stop->schedules.head = createDefaultElem(NULL);
	ListElem* last = stop->schedules.head;
	for (unsigned i = 0; i < length; ++i) {
	last->value = readScheduleFromFile(file);

	}
	last = createElem(NULL, last, NULL);
	}*/
	return stop;

}

//wczytanie wszystkich rozk�ad�w dla danego miasta
void readSchedules(City * city, FILE * file) {
	//dla ka�dego przystanku
	for (size_t i = 0; i < city->busStops.size; ++i) {
		//wczytanie id przystanku i ilo�ci rozk�ad�w
		unsigned busStopID = readInt(file);
		unsigned nSchedules = readInt(file);
		//znalezienie odpoweidniego przystanku w bazie
		ListElem* stopElem = findBusStopById(&city->busStops, busStopID);
		if (stopElem == NULL)
			return;
		BusStop* stop = (BusStop*)stopElem->value;
		if (stop == NULL)
			return;
		initList(&stop->schedules);
		//wczytujemy tyle rozk�ad�w jaka liczba by�a podana w pliku
		for (size_t j = 0; j < nSchedules; ++j) {
			//numer linii
			int lineNumber = readInt(file);
			Schedule* schedule = readScheduleFromFile(file);
			//szukamy odpowiedniej linii w bazie
			ListElem* lineElem = findLineByNumber(&city->busLines, lineNumber);
			Line* line = (Line*)lineElem->value;
			//powi�zanie rozk�adu z konkretn� lini�
			schedule->line = line;
			//dodanie do bazy rozk�adu w danym przystanku
			pushFront(&stop->schedules, schedule);
			pushFront(&line->busStops, stop);
		}
	}
}

//zapisanie do pliku wst�pnych danych o przystanku (bez rozk�ad�w)
void writeBusStopToFile(BusStop * stop, FILE * file) {
	writeInt(stop->id, file);
	writeString(stop->name, file);
}

//zapisanie do pliku rozk�ad�w z danego miasta
void writeSchedules(City * city, FILE * file) {
	//iteracja po li�cie przystank�w
	ListElem* busStopElem = city->busStops.head;
	while (busStopElem != NULL) {
		BusStop* stop = (BusStop*)busStopElem->value;
		//zapisanie id przystanku
		writeInt(stop->id, file);
		writeInt(stop->schedules.size, file);
		//iteracja po elementach listy rozk�ad�w
		ListElem* scheduleElem = stop->schedules.head;
		while (scheduleElem != NULL) {
			//zapisanie danego roz�adu do pliku
			writeScheduleToFile((Schedule*)scheduleElem->value, file);
			scheduleElem = scheduleElem->next;
		}
		busStopElem = busStopElem->next;
	}
}

void removeReferences(BusStop * stop) {
	ListElem* e = stop->schedules.head;
	while (e != NULL) {
		Schedule* schedule = (Schedule*)e->value;
		Line* line = schedule->line;
		removeAll(&line->busStops, stop);
		e = e->next;
	}
}

//wyszukiwanie elementu listy zawieraj�cego przystanek o podanym id
ListElem*findBusStopById(List* list, unsigned id) {
	ListElem* e = list->head;
	while (e != NULL) {
		BusStop* s = (BusStop*)e->value;
		if (s->id == id)
			return e;
		e = e->next;
	}
	return NULL;
}


//wyszukiwanie elementu listy zawieraj�cego przystanek o podanej nazwie
ListElem* findBusStopByName(List* list, const char* name) {
	ListElem* e = list->head;
	while (e != NULL) {
		BusStop* s = (BusStop*)e->value;
		if (strcmp(s->name, name) == 0)
			return e;
		e = e->next;
	}
	return NULL;
}