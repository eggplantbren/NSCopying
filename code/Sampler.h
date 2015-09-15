#ifndef _Sampler_
#define _Sampler_

#include <vector>
#include "RNG.h"

/*
* An object of this class is a classic Nested Sampler.
*/

template<class MyModel>
class Sampler
{
	private:
		// The random number generator to use
		RNG rng;

		// The particles, and information about them
		const int num_particles;
		std::vector<MyModel> particles;
		std::vector<double> log_likelihoods;

		// Whether from_prior has been called on all the particles
		bool initialised;

		// Count number of iterations done
		int iteration;

		// Number of equilibration steps
		int mcmc_steps;

	public:
		// Constructor
		Sampler(int num_particles, int mcmc_steps);

		// Call from_prior on all the particles
		void initialise();

		// Do an iteration of Nested Sampling
		void do_iteration();

		// Do an indefinite number of iterations
		void run();

		// Do a specified number of iterations
		void run(int iterations);
};

#include "SamplerImpl.h"
#endif

