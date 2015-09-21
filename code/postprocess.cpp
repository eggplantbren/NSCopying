#include <iostream>
#include <fstream>
#include "Results.h"
#include "Examples/SpikeSlab.h"

using namespace std;

int main()
{
	Results<SpikeSlab> results;
	results.read_sample_info();
	cout<<"ln(Z) = "<<results.get_log_evidence()<<"."<<endl;
	cout<<"H = "<<results.get_information()<<" nats."<<endl;

	return 0;
}

