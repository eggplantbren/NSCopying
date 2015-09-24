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

	double logZ = results.get_log_evidence();
	double H = results.get_information();
	int N = results.get_num_particles();

	cout<<"ln(Z) = "<<logZ<<" +- "<<sqrt(H/N)<<"."<<endl;
	cout<<"H = "<<H<<" nats."<<endl;

	return 0;
}

