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
		int num_particles;
		std::vector<MyModel> particles;

	public:
		Sampler(int num_particles);


};

#include "SamplerImpl.h"
#endif

