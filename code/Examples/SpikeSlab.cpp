#include "SpikeSlab.h"
#include "Utils.h"
#include <cmath>
#include <limits>

using namespace std;

SpikeSlab::SpikeSlab()
:params(20)
{

}

void SpikeSlab::from_prior(RNG& rng)
{
	for(double& p:params)
		p = -0.5 + rng.rand();
}

double SpikeSlab::perturb(RNG& rng)
{
	int which = rng.rand_int(params.size());
	params[which] += rng.randh();
	wrap(params[which], -0.5, 0.5);
	return 0.;
}

double SpikeSlab::log_likelihood() const
{
	double u = 0.01;
	double v = 0.1;
	double C = log(1.0/sqrt(2*M_PI));
	double logl1 = 0;
	double logl2 = 0;

	for(size_t i=0; i<params.size(); i++)
	{
		logl1 += C - log(u) - 0.5*pow((params[i] - 0.031)/u, 2);
		logl2 += C - log(v) - 0.5*pow(params[i]/v, 2);
	}
	logl1 += log(100.0);

	return logsumexp(logl1, logl2);
}

void SpikeSlab::write(std::ostream& out) const
{
	float temp;
	for(size_t i=0; i<params.size(); i++)
	{
		temp = params[i];
		out.write(reinterpret_cast<char*>(&temp), sizeof(temp));
	}
}

string SpikeSlab::description() const
{
	return string("Each column is one of the 20 parameters.");
}

