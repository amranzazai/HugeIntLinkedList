/*
 * main.cpp
 *
 *  Created on: Mar 9, 2021
 *      Author: amranzazai
 */
#include <iostream>
#include <fstream>
#include <string>

#include "HugeInt.h"

using namespace std;

int main()
{
	ofstream outFile;
	string outFileName;

	HugeInt hi1;
	HugeInt hi2;
	HugeInt hi3;

	for (int i = 0; i < 10; i++){
		hi1.insertDigits(i);
		hi2.insertDigits(i);
	}

	hi1 = hi1 + hi2;
	hi3 = hi1 * hi2;

	if (hi1 == hi2){
		cout << "Equal\n";
	}

	if (hi1 < hi2){
		cout << "hi1 is less than hi2\n";
	}else{
		cout << "hi1 is more than hi2\n";
	}

	cout << "Enter name of output file; press return." << endl;
	cin  >> outFileName;
	outFile.open(outFileName.c_str());

	hi1.write(outFile);
	hi2.write(outFile);
	hi3.write(outFile);

	outFile.close();

	return 0;
};



