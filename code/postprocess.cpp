#include <iostream>
#include <fstream>
#include <ctime>
#include "Results.h"
#include "Examples/SpikeSlab.h"

using namespace std;

int main()
{
	// Make a random number generator
	// in case you want to regenerate the logX values
	RNG rng;
	rng.set_seed(time(0));

	// Read in results
	Results<SpikeSlab> results;
	results.read_sample_info();

	cout<<"ln(Z) = "<<results.get_log_evidence()<<"."<<endl;
	cout<<"H = "<<results.get_information()<<" nats."<<endl;

	return 0;
}

