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
	int timeToFix;

	Patient(std::string a) : name(a), beingServed(false), arrival_time(-1), 
		emergency_start(-1), emergency_finish(-1), severity (-1),  timeToFix (-1){}

	//This operator is not used as we are using a functor but it is here if we ever need it
	bool operator< (const Patient  &other) const{
		return severity < other.severity;
	}
};

#endif