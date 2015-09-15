#include <iostream>
#include <ctime>
#include "Sampler.h"
#include "Examples/SpikeSlab.h"

using namespace std;

int main(int argc, char** argv)
{
	// Create a sampler
	Sampler<SpikeSlab> sampler(1000, 1000);

	// Seed its random number generator
	// Use system time if no seed given on command line
	sampler.set_rng_seed((argc == 1)?(time(0)):(atoi(argv[1])));

	// Do some iterations
	sampler.run(100000);

	return 0;
}

