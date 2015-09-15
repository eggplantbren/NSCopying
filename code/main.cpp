#include <iostream>
#include "Sampler.h"
#include "Examples/SpikeSlab.h"

using namespace std;

int main()
{
	Sampler<SpikeSlab> sampler(1000, 1000);
	sampler.run(100000);

	return 0;
}

