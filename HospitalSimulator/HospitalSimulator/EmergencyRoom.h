#ifndef EMERGENCYROOM_H
#define EMERGENCYROOM_H
#include "WaitingRoom.h"
#include "MedicalPersonel.h"
#include "Doctor.h"
#include "Nurse.h"
#include <vector>
#include <queue>

extern Random my_random;

class EmergencyRoom{
private:
	int num_doctors, num_nurses;
	WaitingRoom * waiting;
	std::vector<MedicalPersonel *> staff;
	int total_wait;
	int num_served;

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
			int time = staff[i]->servePatient(clock, waiting);
			if (time != 0){
				incTime(time);
				num_served++;
			}
			staff[i]->takeNewPatient(clock, waiting);
		}
	}
};
#endif