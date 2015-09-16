#include <iostream>
#include <fstream>
#include "Results.h"
#include "Examples/SpikeSlab.h"

using namespace std;

int main()
{
	Results<SpikeSlab> results;
	results.process_files();

	return 0;
}

