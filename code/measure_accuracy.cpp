/*
* Runs a single sampler repeatedly to estimate the RMS error
* of the log(Z) estimate.
*/

#include <iostream>
#include <fstream>
#include <ctime>
#include "Sampler.h"
#include "Examples/SpikeSlab.h"

using namespace std;

int main(int argc, char** argv)
{
	// Create an RNG
	RNG rng;
	rng.set_seed((argc == 1)?(time(0)):(atoi(argv[1])));

	int num_particles = 50;

	fstream fout("output.txt", ios::out);
	while(true)
	{
		// Create a sampler
		Sampler<SpikeSlab> sampler(num_particles, 100000/num_particles);
		sampler.clear_output_files();
		sampler.set_rng(rng);

		// Do some iterations
		sampler.run(num_particles*100);

		// Output the result (estimated logZ)
		fout<<sampler.get_logZ()<<endl;

		// Get the RNG back so we can continue using the same one
		// next time through the loop
		rng = sampler.get_rng();		
	}
	fout.close();

	return 0;
}


