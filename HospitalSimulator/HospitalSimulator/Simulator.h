#ifndef SIMULATOR_H
#define SIMULATOR_H

#include <iostream>
#include <string>
#include "WaitingRoom.h"
#include "EmergencyRoom.h"
#include "Random.h"


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
	Simulator(){
		waiting = new WaitingRoom();
		emergency = new EmergencyRoom();
	}

	void enter_data(){
		std::cout << "Welcome to CS273ville Hospital!\n";
		int rate = read_int("Please enter arrival rate (planes/hour: ", 1, 60);
		double arrival_rate = rate / 60.0;

		int num_doctors = read_int("Please enter number of doctors working: ", 1, 20);
		int num_nurses = read_int("Please enter number of nurses working: ", 1, 20);
	}
};

#endif