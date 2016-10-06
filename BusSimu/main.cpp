#include "Configuration.h"

using namespace std;

int main() {

	// generate container
	vector<Queue> myQueue;
	vector<Bus> myBus;
	vector<Event> myEventList;
	Configuration myConfig;

	initialize(myConfig);

	config(myQueue, myBus, myConfig, myEventList);
}