#include <fstream>
#include <iostream>
#include <cmath>
#include <limits>
#include "Utils.h"

template<class MyModel>
Results<MyModel>::Results()
:read_sample_info_flag(false)
{

}

template<class MyModel>
void Results<MyModel>::read_sample_info()
{
	// Open the output files (assume standard filenames)
	std::fstream sample_info_file("sample_info.dat", std::ios::in|std::ios::binary);
	if(!sample_info_file)
	{
		std::cerr<<"Error opening sample_info.dat.";
		std::cerr<<std::endl;
		return;
	}

	// Clear the values in memory
	logX.clear();
	log_prior_masses.clear();
	log_likelihoods.clear();

	// Read in the number of particles
	sample_info_file.read(reinterpret_cast<char*>(&num_particles),
									sizeof(num_particles));

	// Read until end of file
	int temp1; double temp2, temp3, temp4;
	while(sample_info_file.read(reinterpret_cast<char*>(&temp1), sizeof(temp1)))
	{
		sample_info_file.read(reinterpret_cast<char*>(&temp2), sizeof(temp2));
		sample_info_file.read(reinterpret_cast<char*>(&temp3), sizeof(temp3));
		sample_info_file.read(reinterpret_cast<char*>(&temp4), sizeof(temp4));

		// Keep the prior and (unnormalised) posterior masses in memory
		logX.push_back(temp2);
		log_likelihoods.push_back(temp3);
	}
	sample_info_file.close();

	// Calculate prior masses
	calculate_prior_masses();

	// Calculate log evidence and information
	calculate_log_evidence();
	calculate_information();

	read_sample_info_flag = true;
}

template<class MyModel>
void Results<MyModel>::calculate_prior_masses()
{
	log_prior_masses.resize(logX.size());
	log_prior_masses[0] = logdiffexp(0., logX[0]);
	for(size_t i=1; i<log_prior_masses.size(); i++)
		log_prior_masses[i] = logdiffexp(logX[i-1], logX[i]);
}

template<class MyModel>
void Results<MyModel>::calculate_log_evidence()
{
	logZ = -std::numeric_limits<double>::max();
	for(size_t i=0; i<log_prior_masses.size(); i++)
		logZ = logsumexp(logZ, log_prior_masses[i] + log_likelihoods[i]);
}

template<class MyModel>
void Results<MyModel>::calculate_information()
{
	H = 0.;

	double logp;
	for(size_t i=0; i<log_prior_masses.size(); i++)
	{
		// Normalised prior mass
		logp = log_prior_masses[i] + log_likelihoods[i] - logZ;
		H += exp(logp)*(logp - log_prior_masses[i]);
	}
}

