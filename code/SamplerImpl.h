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
,tiebreakers(num_particles)
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

	// Open the output files, then close them (erases files)
	sample_file.open("sample.dat", std::ios::out|std::ios::binary);
	sample_info_file.open("sample_info.dat", std::ios::out|std::ios::binary);
	sample_file.close();
	sample_info_file.close();
}

template<class MyModel>
void Sampler<MyModel>::set_rng_seed(unsigned int seed)
{
	rng.set_seed(seed);
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
		tiebreakers[i] = rng.rand();
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
		if(is_below(log_likelihoods[i], tiebreakers[i],
					log_likelihoods[index], tiebreakers[index]))
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

	// Save particle and information to disk
	write_output(index);

	// Shrink prior mass
	log_prior_mass -= 1./num_particles;

	// Remember threshold
	double threshold_log_likelihood = log_likelihoods[index];
	double threshold_tiebreaker = tiebreakers[index];

	// Replace worst particle with a copy
	std::cout<<"# Generating a new particle. Equilibrating..."<<std::flush;
	int copy;
	do
	{
		copy = rng.rand_int(num_particles);
	}while(copy == index);
	particles[index] = particles[copy];
	log_likelihoods[index] = log_likelihoods[copy];
	tiebreakers[index] = tiebreakers[copy];

	// Equilibrate
	double tiebreaker_proposal, logL_proposal, logH;
	int accepted = 0;
	for(int i=0; i<mcmc_steps; i++)
	{
		// Generate proposal
		MyModel proposal = particles[index];
		logH = proposal.perturb(rng);
		tiebreaker_proposal = tiebreakers[index] +
									pow(10., 1.5 - 10.*rng.rand())*rng.randn();
		wrap(tiebreaker_proposal, 0., 1.);

		if(logH != -std::numeric_limits<double>::max())
			logL_proposal = proposal.log_likelihood();

		if(is_below(threshold_log_likelihood, threshold_tiebreaker,
						logL_proposal, tiebreaker_proposal) &&
			rng.rand() <= exp(logH))
		{
			particles[index] = proposal;
			log_likelihoods[index] = logL_proposal;
			tiebreakers[index] = tiebreaker_proposal;
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

template<class MyModel>
void Sampler<MyModel>::write_output(int index)
{
	// Open the output files, to be appended
	sample_file.open("sample.dat", std::ios::out|std::ios::binary|std::ios::app);
	sample_info_file.open("sample_info.dat", std::ios::out|std::ios::binary|std::ios::app);

	// Output the particle
	particles[index].write(sample_file);
	sample_file.close();

	// Output iteration, log prior mass, log likelihood, tiebreaker
	// For single precision output
	float temp1 = log_prior_mass;
	float temp2 = log_likelihoods[index];
	float temp3 = tiebreakers[index];
	sample_info_file.write(reinterpret_cast<char*>(&iteration), sizeof(iteration));
	sample_info_file.write(reinterpret_cast<char*>(&temp1),	sizeof(temp1));
	sample_info_file.write(reinterpret_cast<char*>(&temp2), sizeof(temp2));
	sample_info_file.write(reinterpret_cast<char*>(&temp3), sizeof(temp3));
	sample_info_file.close();
}

template<class MyModel>
bool Sampler<MyModel>::is_below(double log_likelihood1, double tiebreaker1,
									double log_likelihood2, double tiebreaker2)
{
	if(log_likelihood1 < log_likelihood2)
		return true;

	if(log_likelihood1 == log_likelihood2)
	{
		if(tiebreaker1 < tiebreaker2)
			return true;
	}

	return false;
}


