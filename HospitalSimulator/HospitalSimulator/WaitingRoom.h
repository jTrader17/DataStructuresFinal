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



	void update(int clock)
	{
		double a = my_random.next_double();
		if ( a < arrival_rate && totalBeingServed < 2000){
			totalBeingServed++;
			srand(time(NULL));
			int select;
			do{
				select = rand() % town.size();
			} while (town[select]->beingServed);
			town[select]->beingServed = true;
			town[select]->arrival_time = clock;
			int sev_perc, sev;
			sev_perc = rand() % 10;
			if (sev_perc < 7){
				sev = rand() % 10 + 1;
				town[select]->severity = sev;
				minor_queue.push(town[select]);
			}
			else if (sev_perc < 9){
				sev = rand() % 5 + 11;
				town[select]->severity = sev;
				serious_queue.push(town[select]);
			}
			else{
				sev = rand() % 5 + 16;
				town[select]->severity = sev;
				serious_queue.push(town[select]);
			}
		}

	}
	friend class EmergencyRoom;
};

#endif
