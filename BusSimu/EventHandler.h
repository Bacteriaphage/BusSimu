#pragma once
#include <string>
#include <vector>

using namespace std;

enum EVENT_TYPE { PERSON, BOARDING, ARRIVAL };
enum QUEUE_STATUS {ADDING, CLEARING}; // ADD driven by person event, Clearing driven by boarding event;

class Event {
public:
	double _event_time;
	EVENT_TYPE _event_type;
	int _bus_num;
	int _stop_num;

	Event(double event_time, EVENT_TYPE event_type, int bus_num, int stop_num) : _event_time(event_time), _event_type(event_type), _bus_num(bus_num), _stop_num(stop_num) {}

	bool operator < (const Event& other) {
		return (_event_time < other._event_time || (_event_time == other._event_time && _event_type < other._event_type) ||
			(_event_time == other._event_time && _event_type == other._event_type && _bus_num < other._bus_num));
	}
};

class Queue {
public:
	int person = 0;
	int max = INT_MIN;
	int min = INT_MAX;
	vector<unsigned int> sum;
	
};

class Bus {
public:
	unsigned int id;
	vector<double> arrive_time;
	vector<double> depart_time;

	Bus(){}
	Bus(unsigned int id) : id(id){}
};

//this class is package of event operation, queue and bus status
static class EventHandler {
public:
	static void add_event(vector<Event>& event_list, Event event) {
		event_list.push_back(event);
		return;
	}

	static Event get_event(vector<Event>& event_list) {
		Event get = *(event_list.begin());
		event_list.erase(event_list.begin());
		return get;
	}
	
	static void update_queue(vector<Queue>& myQueue, int stop_num, QUEUE_STATUS status) {
		if (status == ADDING) {
			myQueue[stop_num].person++;
			if (myQueue[stop_num].person > myQueue[stop_num].max) {
				myQueue[stop_num].max = myQueue[stop_num].person;
			}
			if (myQueue[stop_num].person < myQueue[stop_num].min) {
				myQueue[stop_num].min = myQueue[stop_num].person;
			}
		}
		else if (status == CLEARING) {
			myQueue[stop_num].sum.push_back(myQueue[stop_num].person);
			myQueue[stop_num].person = 0;
		}
		else {
			throw("status is unclear!");
		}
	}

	static void bus_tracking(vector<Bus>& myBus, int bus_num, double time, bool arrive) {       //be called in arrival event
		if(arrive == true)
			myBus[bus_num].arrive_time.push_back(time);
		else {
			myBus[bus_num].depart_time.push_back(time);
		}
	}
};

