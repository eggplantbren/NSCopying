#ifndef _RNG_
#define _RNG_

#include <random>

class RNG
{
	private:
		// 64-bit Mersenne Twister
		std::mt19937_64 twister;

		// For uniform distribution
		std::uniform_real_distribution<double> uniform;

	public:
		// Constructor
		RNG();

		// Set the seed (obviously)
		void set_seed(unsigned int seed);

		// Uniform(0, 1)
		double rand();
};

#endif

