#ifndef WAITINGROOM_H
#define WAITINGROOM_H

#include <queue>
#include "Patient.h"

extern Random my_random;


class WaitingRoom{
private:
	double arrival_rate;
	std::priority_queue<Patient *> the_queue; 
	int total_wait;  
	int num_served;

public:
	WaitingRoom() : total_wait(0), num_served(0) {}

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
		/* FIXME:  add a new plane into the landing queue based on the arrival_rate
		HINT: my_random.next_double() returns a random value between 0 and 1.
		Read how the the simulation described in the book does this
		(section 6.5 pages. 392-393).
		Look at the Passenger_Queue::check_new_arrival() method
		*/
		if (my_random.next_double() < arrival_rate){
			the_queue.push(new Plane(clock));
		}

	}

	friend class ServiceQueue;
};

#endif
};
#endif