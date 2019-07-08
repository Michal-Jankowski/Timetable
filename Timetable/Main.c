
#include "List.h"
#include "City.h"
#include "Line.h"
#include "BusStop.h"
#include"Interface.h"
#include "DataBase.h"
#include"File.h"
#include<stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "debug.h"
#define BUFSIZE 128

int main(int argc, char *argv[]) {
	//interfejs programu
	char input[BUFSIZE] = { 0 };
	DataBase dataBase;
	char* filename;
	
	 //parametry funkcji main odpowiedzialne za przyjmowanie nazwy pliku

	if (argc != 3) {
		printf("missing parameters");
		return 0;
	}
	if (streq(argv[1], "-o")) {
		filename = argv[2];
		if (!readDataBaseFromFile(filename, &dataBase)) {
			printf("file does not exist\n");
		}
	}
	else {
		printf("missing paramater -o");
		return 0;
	}
	readDataBaseFromFile(filename, &dataBase);
		while (1) { // g³ówny interfejs programu -> komunikacji u¿ytkownika i programu
			printf(">> ");
			getInput(input);
			if (streq(input, "exit")) {
				writeDataBaseToFile(filename, &dataBase);
				break;
			}
			else if (streq(input, "add")) {
				while (1) {
					printf("add >> ");
					getInput(input);
					if (streq(input, "back"))
						break;
					if (streq(input, "busline"))
						addBusLineInterface(&dataBase);
					else if (streq(input, "city"))
						addCityInterface(&dataBase);
					else if (streq(input, "busstoptoline"))
						addBusStoptoLineInterface(&dataBase);
					else if (streq(input, "busstop"))
						addBusStopInterface(&dataBase);
					else if (streq(input, "schedule"))
						setScheduleInterface(&dataBase);
					else
						printf("Invalid input.\n");
				}
				continue;
			}
			else if (streq(input, "delete")) { 
				while (1) {
					printf("delete >> ");
					getInput(input);
					if (streq(input, "back"))
						break;
					if (streq(input, "busline"))
						deleteLineInterface(&dataBase);
					else if (streq(input, "city"))
						deleteCityInterface(&dataBase);
					else if (streq(input, "busstop"))
						deleteBusStopInterface(&dataBase);
					else
						printf("Invalid input.\n");
				}
				continue;
			}
			else if (streq(input, "modify")) {
				while (1) {
					printf("modify >> ");
					getInput(input);
					if (streq(input, "back"))
						break;
					else if (streq(input, "busstop"))
						modifyBusStopInterface(&dataBase);
					else
						printf("Invalid input.\n");
				}
				continue;
			}
			else if (streq(input, "show")) {
				while (1) {
					printf("show >> ");
					getInput(input);
					if (streq(input, "back"))
						break;
					else  if (streq(input, "city"))
						displayCityInterface(&dataBase);
					else if (streq(input, "busstop"))
						displayBusStopInterface(&dataBase);
					else if (streq(input, "busline"))
						displayBusLineInterface(&dataBase);
					else if (streq(input, "timetable"))
						displayTimetableInterface(&dataBase);
					else
						printf("Invalid input.\n");
				}
				continue;
			}
			else
				printf("Invalid input.\n");
		}


	
}
