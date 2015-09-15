#include <iostream>
#include <iomanip>
#include <cstdlib>

template<class MyModel>
Sampler<MyModel>::Sampler(int num_particles)
:num_particles(num_particles)
,particles(num_particles)
,log_likelihoods(num_particles)
,initialised(false)
,iteration(0)
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
	std::cout<<"# Initialising "<<num_particles<<" particles from the prior...";
	std::cout<<std::flush;

	// Generate all particles from the prior
	for(int i=0; i<num_particles; i++)
	{
		particles[i].from_prior();
		log_likelihoods[i] = particles[i].log_likelihood();
	}

	initialised = true;
	std::cout<<"done."<<std::endl;
}

template<class MyModel>
void Sampler<MyModel>::do_iteration()
{
	// Pre-increment iteration
	iteration++;

	// Deterministic estimate of log(X) of the worst particle
	double logX = -static_cast<double>(iteration)/num_particles;

	// Index of the worst particle
	int index = 0;
	double worst = log_likelihoods[0];
	for(int i=1; i<num_particles; i++)
		if(log_likelihoods[i] < log_likelihoods[worst])
			worst = i;

	// Print some information to the screen
	std::cout<<"# Iteration "<<iteration<<", log(X) = ";
	std::cout<<std::setprecision(10)<<logX<", log(L) = ";
	std::cout<<log_likelihoods[worst]<<std::endl;

	// Replace and equilibrate
	
}

