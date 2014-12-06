#ifndef EMERGENCYROOM_H
#define EMERGENCYROOM_H
#include "WaitingRoom.h"
#include <vector>
#include <queue>

extern Random my_random;

class EmergencyRoom{
private:
	int num_doctors, num_nurses;
	WaitingRoom * waiting;
	std::vector<std::queue <Patient *> *> doc_queues;
	std::vector<std::queue <Patient *> *> nurse_queues;
	int total_wait;
	int num_served;

public:
	EmergencyRoom(int nnum, int dnum){
		num_served = 0;
		total_wait = 0;
		num_doctors = dnum;
		num_nurses = nnum;
		
		
	}
	int get_total_wait() {
		return total_wait;
	}

	int get_num_served() {
		return num_served;
	}
	void setWaitingRoom(WaitingRoom * wait){
		waiting = wait;
	}

	void setNumDocs(int num){
		num_doctors = num;
		for (int i = 0; i < num_doctors; i++){
			doc_queues.push_back(new std::queue <Patient *>);
		}
	}
	void setNumNurse(int num){
		num_nurses = num;
		for (int i = 0; i < num_nurses; i++){
			nurse_queues.push_back(new std::queue <Patient *>);
		}
	}
	void update(int clock){
		for (int i = 0; i < num_nurses; i++){
			if (!nurse_queues[i]->empty()){
				Patient * pat = nurse_queues[i]->front();
				if ((clock - pat->emergency_start) > pat->timeToFix){
					pat->emergency_finish = clock;
					int time;
					time = clock - pat->arrival_time;
					total_wait += time;
					num_served++;
					nurse_queues[i]->pop();
				}
			}
		}
		for (int i = 0; i < num_doctors; i++){
			if (!doc_queues[i]->empty()){
				Patient * pat = doc_queues[i]->front();
				if ((clock - pat->emergency_start) > pat->timeToFix){
					pat->emergency_finish = clock;
					int time;
					time = clock - pat->arrival_time;
					total_wait += time;
					num_served++;
					doc_queues[i]->pop();
				}
			}
		}
		for (int i = 0; i < num_nurses; i++){
			if (nurse_queues[i]->empty()){
				if (!waiting->minor_queue.empty()){
					Patient * pat = waiting->minor_queue.top();
					waiting->minor_queue.pop();
					pat->emergency_start = clock;
					pat->timeToFix = my_random.next_int(9) + 1;
					nurse_queues[i]->push(pat);
				}
			}
		}
		for (int i = 0; i < num_doctors; i++){
			if (doc_queues[i]->empty()){
				if (!waiting->serious_queue.empty()){
					Patient * pat = waiting->serious_queue.top();
					waiting->serious_queue.pop();
					pat->emergency_start = clock;
					pat->timeToFix = my_random.next_int(19) + 1;
					doc_queues[i]->push(pat);
				}
				else{
					if (!waiting->minor_queue.empty()){
						Patient * pat = waiting->minor_queue.top();
						waiting->minor_queue.pop();
						pat->emergency_start = clock;
						pat->timeToFix = my_random.next_int(19) + 1;
						doc_queues[i]->push(pat);
					}
				}
			}
		}
	}
};
#endif