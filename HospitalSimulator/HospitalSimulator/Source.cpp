#include <iostream>
#include <cstdlib>
#include <ctime>
#include "Patient.h"
#include <vector>
#include <fstream>
#include <string>
#include "Simulator.h"
using namespace std;

int main(){
	string fileName;
	cout << "Please enter file name: ";
	cin >> fileName;
	vector < Patient * >  the_town;
	ifstream iofile(fileName);
	if (iofile.is_open()){
		string name;
		while (getline(iofile, name))
		{
			int i = 0;
			the_town.push_back(new Patient(name));
			cout << the_town[i] << endl;
			i++;
		}
		iofile.close();
		cout << the_town[0];
		Simulator hospital(the_town);
		hospital.enter_data();
		hospital.run_simulation();
		hospital.show_stats();
	}
	else
		cout << "didnt open" << endl;
}