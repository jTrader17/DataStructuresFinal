#ifndef INFORMATION_H
#define INFORMATION_H
#include <vector>
struct Information{
	int num_times_visited;
	int total_wait_time;
	vector<int> severities;

	double avg_wait_time(){
		return 1.0*num_times_visited / total_wait_time;
	}
};

#endif