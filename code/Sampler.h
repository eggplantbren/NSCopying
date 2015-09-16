#ifndef _Sampler_
#define _Sampler_

#include <vector>
#include <fstream>
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
		std::vector<double> tiebreakers;

		// Whether from_prior has been called on all the particles
		bool initialised;

		// Count number of iterations done
		int iteration;

		// Number of equilibration steps
		int mcmc_steps;

		// Results based on deterministic approximation
		// Log prior mass, log evidence, and information
		double log_prior_mass, log_Z, H;

		// Output file streams
		std::ofstream sample_file, sample_info_file;

		// Method to write a particular particle (and its info) to disk
		void write_output(int index);

		// Function to determine whether one (likelihood, tiebreaker)
		// pair is below another
		static bool is_below(double log_likelihood1, double tiebreaker1,
									double log_likelihood2, double tiebreaker2);

	public:
		// Constructor
		Sampler(int num_particles, int mcmc_steps);

		// Set RNG seed
		void set_rng_seed(unsigned int seed);

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

