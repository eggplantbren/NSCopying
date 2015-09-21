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

		// Read from stream (binary format)
		void read(std::istream& in);

		// Write to stream (binary format)
		void write(std::ostream& out) const;

		// Write to stream (text format)
		void write_text(std::ostream& out) const;
};

#endif

