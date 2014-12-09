#ifndef EMERGENCYROOM_H
#define EMERGENCYROOM_H
#include "WaitingRoom.h"
#include "MedicalPersonel.h"
#include "Doctor.h"
#include "Nurse.h"
#include "Information.h"
#include <vector>
#include <queue>
#include <map>
#include <string>

extern Random my_random;

class EmergencyRoom{
private:
	int num_doctors, num_nurses;
	WaitingRoom * waiting;
	std::vector<MedicalPersonel *> staff;
	int total_wait;
	int num_served;
	std::map <std::string, Information *> my_data;

public:
	EmergencyRoom(){
		num_served = 0;
		total_wait = 0;
	}
	int get_total_wait() {
		return total_wait;
	}

	int get_num_served() {
		return num_served;
	}
	void setWaitingRoom(WaitingRoom * wait){
		waiting = wait;
	}
	void incTime(int more){
		total_wait += more;
	}

	void incNumServed(){
		num_served++;
	}

	void setNumDocs(int num){
		num_doctors = num;
		for (int i = 0; i < num_doctors; i++){
			staff.push_back(new Doctor);
		}
	}
	void setNumNurse(int num){
		num_nurses = num;
		for (int i = 0; i < num_nurses; i++){
			staff.push_back(new Nurse);
		}
	}
	void update(int clock){
		for (int i = 0; i < staff.size(); i++){
			Information * info = staff[i]->servePatient(clock, waiting);
			if (info->total_wait_time != 0){
				incTime(info->total_wait_time);
				num_served++;
				std::map<std::string, Information *>::iterator it;
				it = my_data.find(info->name);
				if (it == my_data.end()){
					std::string name = info->name;
					std::pair<std::string, Information *> newInfo (info->name, info);
					my_data.insert(newInfo);
				}
				else{
					it->second->num_times_visited++;
					it->second->severities.push_back(info->severities[0]);
					it->second->total_wait_time += info->total_wait_time;
				}

			}
			staff[i]->takeNewPatient(clock, waiting);
		}
	}
	void seeAllNames(){
		std::map<std::string, Information *>::iterator it;
		for (it = my_data.begin(); it != my_data.end(); it++){
			std::cout << it->first << std::endl;
		}
	}

	void seeInfo(){
		std::string name;
		std::cout << "Please enter name: ";
		std::cin >> name;
		std::map<std::string, Information *>::iterator it;
		it = my_data.find(name);
		if (it == my_data.end()){
			std::cout << "Name not in database." << std::endl;
		}
		else{
			std::cout << "Name: " << it->first << std::endl
				<< "Number of times visited: " << it->second->num_times_visited << std::endl
				<< "List of severities:\n";
			for (int i = 0; i < it->second->severities.size(); i++){
				std::cout << it->second->severities[i] << " ";
			}
			std::cout << std::endl;
			std::cout << "Average wait time: " << it->second->avg_wait_time() << std::endl;
		}
	}
};
#endif