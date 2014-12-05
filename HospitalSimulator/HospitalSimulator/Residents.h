#ifndef RESIDENTS_H
#define RESIDENTS_H

#include <string>
#include <fstream>
#include <vector>
#include <iostream>
#include "Patient.h"
#include <cstdlib>
#include <ctime>

using namespace std;


class TownResidents{
private:
	vector < Patient * >  the_town;

public:
	TownResidents(std::string fileName){
		fstream iofile(fileName, ios::in);
		string name;
		while (getline(iofile, name))
		{
			the_town.push_back(new Patient(name));
		}
		iofile.close();
	}

	&Patient getRandom(){
		srand(time(NULL));
		do{
			int select = rand() % the_town.size();
		} while (the_town[select]->beingServed);
		the_town[select]->beingServed = true;
		return the_town[select];
	}
};
#endif
