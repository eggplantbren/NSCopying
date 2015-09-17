#ifndef _Results_
#define _Results_

/*
* An object of this class represents a set of results.
* These can be loaded from files, and operations can be performed on them.
*/

#include <vector>

template<class MyModel>
class Results
{
	private:
		// Flag -- whether things have been loaded and calculated
		bool ready;
		std::vector<double> log_prior_mass1, log_prior_mass2;
		std::vector<double> log_likelihoods;

	public:
		Results();
		void process_files();

		double log_evidence1() const;
		double log_evidence2() const;
};

#include "ResultsImpl.h"
#endif

