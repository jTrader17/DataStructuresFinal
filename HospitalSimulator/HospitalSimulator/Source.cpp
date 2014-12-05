#include <iostream>
#include <cstdlib>
#include <ctime>
#include "Patient.h"
#include <vector>
#include <fstream>
#include <string>
using namespace std;

int main(){
	string fileName;
	cout << "Please enter file name: ";
	cin >> fileName;
	vector < Patient * >  the_town;
	fstream iofile(fileName.c_str(), ios::in);
	string name;
	while (getline(iofile, name))
	{
		the_town.push_back(new Patient(name));
	}
	iofile.close();
}