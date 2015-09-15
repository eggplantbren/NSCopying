#include <iostream>
#include "Sampler.h"
#include "RNG.h"

using namespace std;

int main()
{
	cout<<"Hello, world! Here are some random numbers for you:"<<endl<<endl;

	RNG rng;
	for(int i=0; i<10; i++)
		cout<<rng.rand()<<endl;

	return 0;
}

