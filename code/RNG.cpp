#include "RNG.h"

RNG::RNG()
:uniform(0., 1.)
{

}

void RNG::set_seed(unsigned int seed)
{
	twister.seed(seed);
}

double RNG::rand()
{
	return uniform(twister);
}

