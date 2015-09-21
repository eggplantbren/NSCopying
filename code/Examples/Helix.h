#ifndef _Helix_
#define _Helix_

#include <vector>
#include <iostream>
#include "RNG.h"

class Helix
{
	private:
		double x, y, z;

	public:
		Helix();

		// Generate the point from the prior
		void from_prior(RNG& rng);

		// Metropolis-Hastings proposals
		double perturb(RNG& rng);

		// Likelihood function
		double log_likelihood() const;

		// Write to stream (binary format)
		void write(std::ostream& out) const;

		// Return string with column information
		std::string description() const;
};

#endif

