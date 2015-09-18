#include <iostream>
#include <fstream>
#include "Results.h"
#include "Examples/SpikeSlab.h"

using namespace std;

int main()
{
	Results<SpikeSlab> results;
	results.read_sample_info();

	return 0;
}

