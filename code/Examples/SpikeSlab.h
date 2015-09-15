#ifndef _SpikeSlab_
#define _SpikeSlab_

#include <vector>
#include <iostream>
#include "RNG.h"

class SpikeSlab
{
	private:
		std::vector<double> params;

	public:
		SpikeSlab();

		// Generate the point from the prior
		void from_prior(RNG& rng);

		// Metropolis-Hastings proposals
		double perturb(RNG& rng);

		// Likelihood function
		double log_likelihood() const;

		// Print to stream
		void print(std::ostream& out) const;

		// Return string with column information
		std::string description() const;
};

#endif

