#ifndef _Results_
#define _Results_

/*
* An object of this class represents a set of results from a *single*
* Nested Sampling run.
* These can be loaded from files, and operations can be performed on them.
*/

#include <vector>

template<class MyModel>
class Results
{
	private:
		// Flag -- whether read_sample_info() has been called
		bool read_sample_info_flag;
		int num_particles;
		std::vector<double> logX;
		std::vector<double> log_prior_masses;
		std::vector<double> log_likelihoods;

		// log evidence and information
		double logZ, H;

		// Methods that calculate the above
		void calculate_prior_masses();
		void calculate_log_evidence();
		void calculate_information();

	public:
		Results();
		void read_sample_info();

		// Getters
		double get_log_evidence() const
		{ return logZ; }
		double get_information() const
		{ return H; }
};

#include "ResultsImpl.h"
#endif

