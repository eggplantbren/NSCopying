#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <limits>
#include "Utils.h"

template<class MyModel>
Sampler<MyModel>::Sampler(int num_particles, int mcmc_steps)
:num_particles(num_particles)
,particles(num_particles)
,log_likelihoods(num_particles)
,initialised(false)
,iteration(0)
,mcmc_steps(mcmc_steps)
,log_prior_mass(log(1. - exp(-1./num_particles)))
,log_Z(-std::numeric_limits<double>::max())
,H(0.)
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

	// Find the index of the worst particle
	int index = 0;
	for(int i=1; i<num_particles; i++)
		if(log_likelihoods[i] < log_likelihoods[index])
			index = i;

	// Update estimates based on deterministic approximation
	// on the fly. From appendix of Skilling (2006)
	double log_posterior_mass = log_prior_mass + log_likelihoods[index];
	double log_Z_new = logsumexp(log_Z, log_posterior_mass);
	H = exp(log_posterior_mass - log_Z_new)*log_likelihoods[index]
		+ exp(log_Z - log_Z_new)*(H + log_Z) - log_Z_new;
	log_Z = log_Z_new;

	// Print some information to the screen
	std::cout<<"# Iteration "<<iteration<<", log(X) = ";
	std::cout<<std::setprecision(10)<<logX<<", log(L) = ";
	std::cout<<log_likelihoods[index]<<"."<<std::endl;
	std::cout<<"# log(Z) = "<<log_Z<<", H = "<<H<<"."<<std::endl;
	std::cout<<"# Generating a new particle. Equilibrating..."<<std::flush;

	// Shrink prior mass
	log_prior_mass -= 1./num_particles;

	// Replace worst particle with a copy
	double threshold = log_likelihoods[index];	// Remember threshold
	int copy;
	do
	{
		copy = rng.rand_int(num_particles);
	}while(copy == index);
	particles[index] = particles[copy];
	log_likelihoods[index] = log_likelihoods[copy];

	// Equilibrate
	double logL_proposal, logH;
	int accepted = 0;
	for(int i=0; i<mcmc_steps; i++)
	{
		MyModel proposal = particles[index];
		logH = proposal.perturb(rng);
		if(logH != -std::numeric_limits<double>::max())
			logL_proposal = proposal.log_likelihood();

		if(logL_proposal >= threshold && rng.rand() <= exp(logH))
		{
			particles[index] = proposal;
			log_likelihoods[index] = logL_proposal;
			accepted++;
		}
	}
	std::cout<<"done. Accepted "<<accepted<<"/"<<mcmc_steps<<".";
	std::cout<<std::endl<<std::endl;
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

