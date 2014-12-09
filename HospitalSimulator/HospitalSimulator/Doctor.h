#ifndef DOCTOR_H
#define DOCTOR_H
#include "MedicalPersonel.h"
#include "WaitingRoom.h"
//#include "EmergencyRoom.h"

extern Random my_random;

class Doctor : public MedicalPersonel{
public:
	Doctor(){};
	int servePatient(int clock, WaitingRoom * waiting){
		if (!currentServing.empty()){
			Patient * pat = currentServing.front();
			if ((clock - pat->emergency_start) > pat->timeToFix){
				waiting->decServed();
				pat->emergency_finish = clock;
				pat->beingServed = false;
				int time;
				time = clock - pat->arrival_time;
				currentServing.pop();
				return time;
			}
		}
	}
	void takeNewPatient(int clock, WaitingRoom * waiting){
		if (currentServing.empty()){
			if (!waiting->seriousEmpty()){
				Patient * pat = waiting->seriousTop();
				pat->emergency_start = clock;
				pat->timeToFix = my_random.next_int(19) + 1;
				currentServing.push(pat);
			}
			else{
				if (!waiting->minorEmpty()){
					Patient * pat = waiting->minorTop();
					pat->emergency_start = clock;
					pat->timeToFix = my_random.next_int(19) + 1;
					currentServing.push(pat);
				}
			}
		}
	}
};
#endif