#ifndef SIMULATOR_H
#define SIMULATOR_H

#include <iostream>
#include <string>
#include "WaitingRoom.h"
#include "EmergencyRoom.h"
#include "Random.h"
#include <vector>


Random my_random;

class Simulator {
private:
	int total_time = 24*60*7;
	int clock;

	WaitingRoom *waiting;
	EmergencyRoom *emergency;

	int read_int(const std::string &prompt, int low, int high)
	{
		if (low >= high) // invalid range
			throw std::invalid_argument("invalid range specified");

		std::cin.exceptions(std::ios_base::failbit);
		int num = 0;
		while (true) {
			try {
				while (true) {
					std::cout << prompt;
					std::cin >> num;
					if (num >= low && num <= high) { // within the specified range
						std::cout << std::endl;
						return num;
					}
				}
			}
			catch (std::ios_base::failure) {
				std::cout << "Bad numeric string -- try again\n";
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<int>::max(), '\n');
			}
		}
	}

public:
	Simulator(vector<Patient *>  town ){
		waiting = new WaitingRoom(town);
		emergency = new EmergencyRoom(-1, -1);
	}

	void enter_data(){
		std::cout << "Welcome to CS273ville Hospital!\n";
		int rate = read_int("Please enter arrival rate (patients/hour): ", 1, 60);
		double arrival_rate = rate / 60.0;

		int num_doctors = read_int("Please enter number of doctors working: ", 1, 20);
		emergency->setNumDocs(num_doctors);
		int num_nurses = read_int("Please enter number of nurses working: ", 1, 20);
		emergency->setNumNurse(num_nurses);
		emergency->setWaitingRoom(waiting);
	}
	void run_simulation(){
		for (clock = 0; clock < total_time; clock++){
			waiting->update(clock);
			emergency->update(clock);
		}
	}

	void show_stats(){
		std::cout << "Number of patients served: " << emergency->get_num_served() << endl;
		std::cout << "Total time waited by patients (min): " << emergency->get_total_wait() << endl;
		double average = 1.0*emergency->get_total_wait() / emergency->get_num_served();
		std::cout << "Average time waited per patient (min): " << average << endl;
	}
};

#endif