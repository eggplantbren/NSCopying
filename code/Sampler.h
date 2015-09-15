#ifndef _Sampler_
#define _Sampler_

#include <vector>

/*
* An object of this class is a classic Nested Sampler.
*/

template<class MyModel>
class Sampler
{
	private:
		// The particles, and information about them
		const int num_particles;
		std::vector<MyModel> particles;
		std::vector<double> log_likelihoods;

		// Whether from_prior has been called on all the particles
		bool initialised;

	public:
		// Constructor
		Sampler(int num_particles);

		// Call from_prior on all the particles
		void initialise();


};

#include "SamplerImpl.h"
#endif

