#ifndef INFORMATION_H
#define INFORMATION_H
#include <vector>
#include <string>
class Information{
public:
	std::string name;
	int num_times_visited;
	int total_wait_time;
	std::vector<int> severities;
	

	double avg_wait_time(){
		return 1.0*total_wait_time/num_times_visited;
	}
	Information(){
		name = "";
		num_times_visited = 0;
		total_wait_time = 0;
	}
	Information(std::string name, int time, int severity){
		this->name = name;
		num_times_visited = 1;
		total_wait_time = time;
		severities.push_back(severity);

	}
};

#endif