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
	int total_time = 10080;
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
	Simulator(std::vector<Patient *>  town ){
		waiting = new WaitingRoom(town);
		emergency = new EmergencyRoom();
	}

	void enter_data(){
		std::cout << "Welcome to CS273ville Hospital!\n";
		//rate must be between 1-60
		int rate = read_int("Please enter arrival rate (patients/hour): ", 1, 60);
		double arrival_rate = rate / 60.0;
		waiting->set_arrival_rate(arrival_rate);
		//number of nurses must be between 1-20
		int num_nurses = read_int("Please enter number of nurses working: ", 1, 20);
		emergency->setNumNurse(num_nurses);
		//number of doctors must be between 1-20
		int num_doctors = read_int("Please enter number of doctors working: ", 1, 20);
		emergency->setNumDocs(num_doctors);
		emergency->setWaitingRoom(waiting);
	}
	void run_simulation(){
		for (clock = 0; clock < total_time; clock++){
			waiting->update(clock);
			emergency->update(clock);
		}
	}

	void show_stats(){
		std::cout << "Number of patients served: " << emergency->get_num_served() << std::endl;
		std::cout << "Total time waited by patients (min): " << emergency->get_total_wait() << std::endl;
		double average = 1.0*emergency->get_total_wait() / emergency->get_num_served();
		std::cout << "Average visit time per patient (min): " << average << std::endl;
	}

	void post_simulation(){
		//Post-simulation ui
		int select = 0;
		while (select != 3){
			std::cout << "What would you like to do?\n";
			std::cout << "1) See names of all those who were treated by the hospital\n";
			std::cout << "2) See details of a certain patient\n";
			std::cout << "3) Exit\n";
			std::cin >> select;

			if (select == 1){
				emergency->seeAllNames();
			}
			if (select == 2){
				emergency->seeInfo();
			}
		}
	}
};

#endif