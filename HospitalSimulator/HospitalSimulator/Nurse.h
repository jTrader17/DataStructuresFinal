#ifndef NURSE_H
#define NURSE_H
#include "MedicalPersonel.h"
#include "WaitingRoom.h"
#include "Information.h"

extern Random my_random;

class Nurse: public MedicalPersonel {
public:
	Nurse(){};
	Information * servePatient(int clock, WaitingRoom * waiting){
		if (!currentServing.empty()){
			Patient * pat = currentServing.front();
			if ((clock - pat->emergency_start) > pat->timeToFix){
				waiting->decServed();
				pat->emergency_finish = clock;
				pat->beingServed = false;
				int time;
				time = clock - pat->arrival_time;
				currentServing.pop();
				return new Information(pat->name, time, pat->severity);
			}
		}
		return new Information;
	}

	void takeNewPatient(int clock, WaitingRoom * waiting){
		if (currentServing.empty()){
			if (!waiting->minorEmpty()){
				Patient * pat = waiting->minorTop();
				pat->emergency_start = clock;
				pat->timeToFix = my_random.next_int(9) + 1;
				currentServing.push(pat);
			}
		}
	}
};
#endif