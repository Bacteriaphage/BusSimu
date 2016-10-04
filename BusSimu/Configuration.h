#pragma once

class Configuration {
	unsigned int stop_num;
	unsigned int bus_num;
	double boarding_time;
	double arriving_mean_time;
	double driving_time;

	Configuration(){}
	Configuration(unsigned int stop, unsigned int bus, double boarding, double arriving, double driving) : stop_num(stop)
		, bus_num(bus), boarding_time(boarding), arriving_mean_time(arriving), driving_time(driving){}
};