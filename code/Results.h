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
		std::vector<double> log_prior_mass;
		std::vector<double> log_posterior_mass;	// Unnormalised

	public:
		Results();
		void process_files();
};

#include "ResultsImpl.h"
#endif

