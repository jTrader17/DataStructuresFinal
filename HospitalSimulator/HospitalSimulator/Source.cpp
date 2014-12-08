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
	string fileName = "residents_273ville.txt";
	vector < Patient * >  the_town;
	fstream fs;
	fs.open("residents_273ville.txt");
	if (fs.is_open()){
		string name ="start";
		//while (getline(fs, name))
		int i = 0;
		while (!fs.eof())
		{
			fs >> name;
			the_town.push_back(new Patient(name));
		}
		fs.close();
		Simulator hospital(the_town);
		hospital.enter_data();
		hospital.run_simulation();
		hospital.show_stats();
	}
	else
		cout << "didnt open" << endl;
}