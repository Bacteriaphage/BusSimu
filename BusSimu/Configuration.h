#pragma once

#include <sstream>
#include <fstream>
#include <map>
#include "EventHandler.h"
using namespace std;



class Configuration {
public:
	unsigned int stop_num = NULL;
	unsigned int bus_num = NULL;
	double boarding_time = NULL;
	double arriving_mean_time = NULL;
	double driving_time = NULL;

	Configuration(){}
	Configuration(unsigned int stop, unsigned int bus, double boarding, double arriving, double driving) : stop_num(stop)
		, bus_num(bus), boarding_time(boarding), arriving_mean_time(arriving), driving_time(driving){}
};

void initialize(Configuration& myConfig) {  //read config file and initialize Configuration
	map<string, int> myMap;
	myMap["stop_num"] = 1;
	myMap["bus_num"] = 2;
	myMap["boarding_time"] = 3;
	myMap["arriving_mean_time"] = 4;
	myMap["driving_time"] = 5;

	string line, attribute;
	ifstream input("config.txt");
	while (getline(input, line)) {
		istringstream mystream(line);
		mystream >> attribute;
		switch (myMap[attribute]) {
		case 1: {
			int value;
			mystream >> value;
			myConfig.stop_num = value;
			break;
		}
		case 2: {
			int value;
			mystream >> value;
			myConfig.bus_num = value;
			break;
		}
		case 3: {
			double value;
			mystream >> value;
			myConfig.boarding_time = value;
			break;
		}
		case 4: {
			double value;
			mystream >> value;
			myConfig.arriving_mean_time = value;
			break;
		}
		case 5:{
			double value;
			mystream >> value;
			myConfig.driving_time = value;
			break;
		}
		default:
			break;
		}
	}
	if (myConfig.stop_num == NULL || myConfig.bus_num == NULL || myConfig.boarding_time == NULL || 
		myConfig.arriving_mean_time == NULL || myConfig.driving_time == NULL) {
		throw ("initialization fail!");
	}
}

void config(vector<Queue>& myQueue, vector<Bus>& myBus, const Configuration& myConfig, vector<Event>& myEventList) { //initial container of bus and bus stop and eventList
	for (int i = 0; i < myConfig.stop_num; i++) {
		myQueue.push_back(Queue());
		myEventList.push_back(Event(0.0, PERSON, 0, i));    //Person event
	}
	for (int i = 0; i < myConfig.bus_num;i++) {
		myBus.push_back(Bus(i+1));
		myEventList.push_back(Event(0.0, ARRIVAL, i, myConfig.stop_num / myConfig.bus_num * i));   //Arrival event
	}
}