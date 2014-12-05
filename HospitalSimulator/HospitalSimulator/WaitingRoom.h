#ifndef WAITINGROOM_H
#define WAITINGROOM_H

#include <queue>
#include "Random.h"
#include "Residents.h"

extern Random my_random;


class WaitingRoom{
private:
	double arrival_rate;
	std::priority_queue<Patient *> the_queue; 
	int total_wait;  
	int num_served;
	TownResidents town;

public:
	WaitingRoom(TownResidents a) : total_wait(0), num_served(0), town(a){}

	void set_arrival_rate(double arrival_rate) {
		this->arrival_rate = arrival_rate;
	}

	int get_total_wait() {
		return total_wait;
	}

	int get_num_served() {
		return num_served;
	}

	void update(int clock)
	{
		if (my_random.next_double() < arrival_rate){
			Patient * p = town.getRandom();
			p->emergency_start(clock);
			the_queue.push(p);
		}

	}

	friend class ServiceQueue;
};

#endif
