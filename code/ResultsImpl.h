#include <fstream>
#include <iostream>
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
	log_prior_mass1.clear();
	log_prior_mass2.clear();
	log_likelihoods.clear();

	// Read until end of file
	int temp1; float temp2, temp3, temp4, temp5;
	while(sample_info_file.read(reinterpret_cast<char*>(&temp1), sizeof(temp1)))
	{
		sample_info_file.read(reinterpret_cast<char*>(&temp2), sizeof(temp2));
		sample_info_file.read(reinterpret_cast<char*>(&temp3), sizeof(temp3));
		sample_info_file.read(reinterpret_cast<char*>(&temp4), sizeof(temp4));
		sample_info_file.read(reinterpret_cast<char*>(&temp5), sizeof(temp5));

		// Keep the prior and (unnormalised) posterior masses in memory
		log_prior_mass1.push_back(temp2);
		log_prior_mass2.push_back(temp3);
		log_likelihoods.push_back(temp4);
	}
	sample_info_file.close();

	// Normalise prior weights
	double diff = logsumexp(log_prior_mass1);
	for(size_t i=0; i<log_prior_mass1.size(); i++)
		log_prior_mass1[i] -= diff;
	diff = logsumexp(log_prior_mass2);
	for(size_t i=0; i<log_prior_mass2.size(); i++)
		log_prior_mass2[i] -= diff;

	read_sample_info_flag = true;
}

template<class MyModel>
double Results<MyModel>::log_evidence1() const
{
	double logZ = -std::numeric_limits<double>::max();
	for(size_t i=0; i<log_prior_mass1.size(); i++)
		logZ = logsumexp(logZ, log_prior_mass1[i] + log_likelihoods[i]);
	return logZ;
}

template<class MyModel>
double Results<MyModel>::log_evidence2() const
{
	double logZ = -std::numeric_limits<double>::max();
	for(size_t i=0; i<log_prior_mass2.size(); i++)
		logZ = logsumexp(logZ, log_prior_mass2[i] + log_likelihoods[i]);
	return logZ;
}

