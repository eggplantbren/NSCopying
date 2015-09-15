#include <iostream>
#include <iomanip>
#include <cstdlib>

template<class MyModel>
Sampler<MyModel>::Sampler(int num_particles, int mcmc_steps)
:num_particles(num_particles)
,particles(num_particles)
,log_likelihoods(num_particles)
,initialised(false)
,iteration(0)
,mcmc_steps(mcmc_steps)
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
		particles[i].from_prior(rng);
		log_likelihoods[i] = particles[i].log_likelihood();
	}
	initialised = true;
	std::cout<<"done."<<std::endl<<std::endl;
}

template<class MyModel>
void Sampler<MyModel>::do_iteration()
{
	if(!initialised)
		initialise();

	// Pre-increment iteration
	iteration++;

	// Deterministic estimate of log(X) of the worst particle
	double logX = -static_cast<double>(iteration)/num_particles;

	// Index of the worst particle
	int index = 0;
	for(int i=1; i<num_particles; i++)
		if(log_likelihoods[i] < log_likelihoods[index])
			index = i;

	double threshold = log_likelihoods[index];

	// Print some information to the screen
	std::cout<<"# Iteration "<<iteration<<", log(X) = ";
	std::cout<<std::setprecision(10)<<logX<<", log(L) = ";
	std::cout<<log_likelihoods[index]<<std::endl;

	std::cout<<"# Generating a new particle. Equilibrating..."<<std::flush;

	// Replace worst particle with a copy
	int copy;
	do
	{
		copy = rng.rand_int(num_particles);
	}while(copy == index);
	particles[index] = particles[copy];
	log_likelihoods[index] = log_likelihoods[copy];

	// Equilibrate
	double logL_proposal, logH;
	for(int i=0; i<mcmc_steps; i++)
	{
		MyModel proposal = particles[index];
		logH = proposal.perturb(rng);
		if(logH != -1E300)
			logL_proposal = proposal.log_likelihood();

		if(logL_proposal >= threshold && rng.rand() <= exp(logH))
		{
			particles[index] = proposal;
			log_likelihoods[index] = logL_proposal;
		}
	}
	std::cout<<"done."<<std::endl<<std::endl;
}

template<class MyModel>
void Sampler<MyModel>::run()
{
	while(true)
		do_iteration();
}

template<class MyModel>
void Sampler<MyModel>::run(int iterations)
{
	for(int i=0; i<iterations; i++)
		do_iteration();
}

