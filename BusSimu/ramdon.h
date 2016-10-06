#pragma once

#include <time.h>
#include <math.h>

#define A      16807L
#define M      2147483647L
#define Q      127773L
#define R      2836L
#define FLOATM 2147483647.0
/* This is the initial seed value. It can be set by a call to seturand. */
static long seed = 1;

/* This function returns a floating point number uniformly distributed 0 < furand() <= 1.0 */
double furand() {
	long lo;
	long hi;
	long test;
	hi = seed / Q;
	lo = seed % Q;
	test = A * lo - R * hi;
	if (test > 0)
		seed = test;
	else
		seed = test + M;
	return ((double)seed / FLOATM);
}

/* This function returns a long integer number uniformly distributed 0 < urand() <= 2,147,483,647 (almost 2**31)*/
long urand() {
	long lo;
	long hi;
	long test;
	hi = seed / Q;
	lo = seed % Q;
	test = A * lo - R * hi;
	if (test > 0)
		seed = test;
	else
		seed = test + M;
	return (seed);
}

/* function to return an exponentially random number in the range from zero to infinity with the specified mean.*/
double exprand(double mean) {
	return(-mean * log(furand()));
}

/* This function can be used to initialize the seed for the random number generator.*/
void seturand(long newseed) {
	seed = newseed % M; /* assure seed is within range */
}

/* This function initializes the random number seed to the time */
void urandini(void) {
	seed = (long)time(NULL) % M;
}
