#ifndef MEDICALPERSONEL_H
#define MEDICALPERSONEL_H
#include <vector>
#include <queue>
#include "Patient.h"
#include "WaitingRoom.h"
//#include "EmergencyRoom.h"
class MedicalPersonel{
protected:
	std::queue <Patient *> currentServing;
public:
	virtual int servePatient(int clock, WaitingRoom * waiting) = 0;
	virtual void takeNewPatient(int clock, WaitingRoom * waiting) = 0;
};

#endif