#include <iostream>
#include <cstdlib>

template<class MyModel>
Sampler<MyModel>::Sampler(int num_particles)
:num_particles(num_particles)
,particles(num_particles)
,log_likelihoods(num_particles)
,initialised(false)
{
	// Check for a sensible input value
	if(num_particles <= 0)
	{
		std::cerr<<"# ERROR: Bad number of particles."<<std::endl;
		exit(1);
	}
	if(num_particles > 10000)
		std::cerr<<"# WARNING: Very large number of particles."<<std::endl;
}

template<class MyModel>
void Sampler<MyModel>::initialise()
{
	for(MyModel& p: particles)
		p.from_prior();

	initialised = true;
}
