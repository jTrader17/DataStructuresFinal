#ifndef PATIENT_H
#define PATIENT_H

#include "string.h"

struct Patient{
	std::string name;
	bool beingServed;
	int arrival_time;
	int emergency_start;
	int emergency_finish;
	int severity;

	Patient(std::string a) : name(a), beingServed(false), arrival_time(-1), 
		emergency_start(-1), emergency_finish(-1), severity (-1) {}

	bool operator> (Patient * other){
		if (this->severity > other->severity)
			return true;
		else
			return false;
	}
};

#endif