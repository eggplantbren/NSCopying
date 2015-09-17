#include <fstream>
#include <iostream>

template<class MyModel>
Results<MyModel>::Results()
:ready(false)
{

}

template<class MyModel>
void Results<MyModel>::process_files()
{
	// Open the output files (assume standard filenames)
	std::fstream sample_file("sample.dat", std::ios::in|std::ios::binary);
	std::fstream sample_info_file("sample_info.dat", std::ios::in|std::ios::binary);
	if(!sample_file || !sample_info_file)
	{
		std::cerr<<"Error opening either sample.dat or sample_info.dat.";
		std::cerr<<std::endl;
		return;
	}

	// Clear the values in memory
	log_prior_mass.clear();
	log_posterior_mass.clear();

	// Read until end of file
	int temp1; float temp2, temp3, temp4, temp5;
	while(sample_info_file.read(reinterpret_cast<char*>(&temp1), sizeof(temp1)))
	{
		sample_info_file.read(reinterpret_cast<char*>(&temp2), sizeof(temp2));
		sample_info_file.read(reinterpret_cast<char*>(&temp3), sizeof(temp3));
		sample_info_file.read(reinterpret_cast<char*>(&temp4), sizeof(temp4));
		sample_info_file.read(reinterpret_cast<char*>(&temp5), sizeof(temp5));

		// Keep the prior and (unnormalised) posterior masses in memory
		log_prior_mass.push_back(temp2);
		log_posterior_mass.push_back(temp1 + temp2);
	}
	sample_file.close();
	sample_info_file.close();

	ready = true;
}

