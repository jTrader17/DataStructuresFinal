#ifndef WAITINGROOM_H
#define WAITINGROOM_H

#include <queue>
#include "Random.h"
#include <vector>
#include "Patient.h"
#include <cstdlib>
#include <ctime>
#include "Node_Comparison.h"

extern Random my_random;


class WaitingRoom{
private:
	int totalBeingServed;
	double arrival_rate;
	std::priority_queue<Patient *, std::vector<Patient *>, Node_Comparison> serious_queue; 
	std::priority_queue<Patient *, std::vector<Patient *>, Node_Comparison> minor_queue;
	std::vector<Patient *> town;

public:
	WaitingRoom(std::vector<Patient *> a) : town(a){
		totalBeingServed = 0;
	}

	void set_arrival_rate(double arrival_rate) {
		this->arrival_rate = arrival_rate;
	}

	void decServed(){
		totalBeingServed--;
	}

	bool minorEmpty(){
		return minor_queue.empty();
	}

	bool seriousEmpty(){
		return serious_queue.empty();
	}

	Patient * minorTop(){
		Patient * pat = minor_queue.top();
		minor_queue.pop();
		return pat;
	}

	Patient * seriousTop(){
		Patient * pat = serious_queue.top();
		serious_queue.pop();
		return pat;
	}

	void update(int clock)
	{
		double a = my_random.next_double();
		if ( a < arrival_rate && totalBeingServed < 1999){
			totalBeingServed++;
			int select;
			do{
				select = my_random.next_int(town.size() - 1);
			} while (town[select]->beingServed);
			town[select]->beingServed = true;
			town[select]->arrival_time = clock;
			int sev_perc, sev;
			sev_perc = my_random.next_int(9);
			if (sev_perc < 7){
				sev = my_random.next_int(9)+1;
				town[select]->severity = sev;
				minor_queue.push(town[select]);
			}
			else if (sev_perc < 9){
				sev = my_random.next_int(4) + 11;
				town[select]->severity = sev;
				serious_queue.push(town[select]);
			}
			else{
				sev = my_random.next_int(4) + 16;
				town[select]->severity = sev;
				serious_queue.push(town[select]);
			}
		}

	}
	friend class EmergencyRoom;
};

#endif
