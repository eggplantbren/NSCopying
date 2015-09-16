#include <iostream>
#include <fstream>
#include "Utils.h"
#include "Examples/SpikeSlab.h"

using namespace std;

int main()
{
	fstream sample_file("sample.dat", ios::in|ios::binary);
	fstream sample_info_file("sample_info.dat", ios::in|ios::binary);

	int temp1; float temp2; float junk;
	while(sample_info_file.read(reinterpret_cast<char*>(&temp1), sizeof(temp1)))
	{
		sample_info_file.read(reinterpret_cast<char*>(&temp2), sizeof(temp2));
		sample_info_file.read(reinterpret_cast<char*>(&junk), sizeof(junk));
		sample_info_file.read(reinterpret_cast<char*>(&junk), sizeof(junk));
		cout<<temp2<<endl;
	}
	

	sample_file.close();
	sample_info_file.close();
	return 0;
}

