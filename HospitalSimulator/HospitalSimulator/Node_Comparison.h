#ifndef NODE_COMPARISON_H
#define NODE_COMPARISON_H
#include <iostream>
#include "Patient.h"

struct Node_Comparison{
	bool operator() (const Patient * a, const Patient * b ) const{
		return (a->severity < b->severity);
	}
};
#endif