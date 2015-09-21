#include "Helix.h"
#include "Utils.h"
#include <cmath>
#include <limits>

using namespace std;

Helix::Helix()
{

}

void Helix::from_prior(RNG& rng)
{
	x = rng.rand();
	y = rng.rand();
	z = rng.rand();
}

double Helix::perturb(RNG& rng)
{
	int which = rng.rand_int(3);
	double* param;
	if(which == 0)
		param = &x;
	else if(which == 1)
		param = &y;
	else
		param = &z;

	*param += rng.randh();
	wrap(*param, 0., 1.);

	return 0.;
}

double Helix::log_likelihood() const
{
	double logL = 0.;

	double rsq = x*x + y*y;
	logL += -0.5*(rsq - 0.25)/1E-6;
	logL += -0.5*pow(tan(z) - y/x, 2)/1E-6;
	return logL;
}

void Helix::write(std::ostream& out) const
{
	float temp;
	temp = x;
	out.write(reinterpret_cast<char*>(&temp), sizeof(temp));
	temp = y;
	out.write(reinterpret_cast<char*>(&temp), sizeof(temp));
	temp = z;
	out.write(reinterpret_cast<char*>(&temp), sizeof(temp));
}

string Helix::description() const
{
	return string("Each column is one of the 20 parameters.");
}

