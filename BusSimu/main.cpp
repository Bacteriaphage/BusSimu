#include "Configuration.h"
#include "ramdon.h"
#include <iostream>
#include <algorithm>
using namespace std;

int main() {

	// generate container
	vector<Queue> myQueue;
	vector<Bus> myBus;
	vector<Event> myEventList;
	Configuration myConfig;
	initialize(myConfig);

	config(myQueue, myBus, myConfig, myEventList);

	double clock(0.0), stop_time(28800);
	try {
		do {
			Event this_event = EventHandler::get_event(myEventList);
			clock = this_event._event_time;
			switch (this_event._event_type) {
			case PERSON: {
				EventHandler::add_event(myEventList, Event(clock + exprand(myConfig.arriving_mean_time), PERSON, 0, this_event._stop_num));
				EventHandler::update_queue(myQueue, this_event._stop_num, ADDING);
				break;
			}
			case ARRIVAL: {
				EventHandler::add_event(myEventList, Event(clock, BOARDING, this_event._bus_num, this_event._stop_num));
				EventHandler::bus_tracking(myBus, this_event._bus_num, clock);
				break;
			}
			case BOARDING: {
				EventHandler::add_event(myEventList, Event(clock + myQueue[this_event._stop_num].person * myConfig.boarding_time
					+ myConfig.driving_time, ARRIVAL, this_event._bus_num, (this_event._stop_num + 1) % myConfig.stop_num));
				EventHandler::update_queue(myQueue, this_event._stop_num, CLEARING);
				break;
			}
			default:
				break;
			}
			sort(myEventList.begin(), myEventList.end());
		} while (clock < stop_time);
	}
	catch (string exception) {
		cout << exception;
	}

	for (int i = 0; i < myQueue.size();i++) {
		float average = 0.0;
		cout << "Stop No." << i + 1 << ": max " << myQueue[i].max << " min " << myQueue[i].min << ' ';
		for (int j = 0; j < myQueue[i].sum.size(); j++) {
			average += myQueue[i].sum[j];
		}
		average /= myQueue[i].sum.size();
		cout << "avg " << average << endl;
	}

	ofstream output("bus_record.txt");

	for (int i = 0; i < myBus.size(); i++) {
		output << "Bus No." << i+1 << ':';
		for (int j = 0; j < myBus[i].arrive_time.size(); j++) {
			if (!(j % 5)) {
				output << endl;
			}
			output << myBus[i].arrive_time[j] << " ";
		}
		output << endl;
	}
	return 0;
}