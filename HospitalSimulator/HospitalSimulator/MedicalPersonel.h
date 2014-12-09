#ifndef MEDICALPERSONEL_H
#define MEDICALPERSONEL_H
#include <vector>
#include <queue>
#include "Patient.h"
#include "WaitingRoom.h"
#include "Information.h"
class MedicalPersonel{
protected:
	std::queue <Patient *> currentServing;
public:
	virtual Information * servePatient(int clock, WaitingRoom * waiting) = 0;
	virtual void takeNewPatient(int clock, WaitingRoom * waiting) = 0;
};

#endif