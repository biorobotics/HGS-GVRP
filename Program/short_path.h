

#ifndef short_path
#define short_path

#include "vector" 
#include "./Params.h"

struct Nodesp
{
	int cour;			// Node index
	int prev;						// previous node in the route
	double cost;					//Cost to reach the node
	bool checkFlag;					//One if the node must be checked zero otherwise
	bool checked;
	Nodesp(int cour, double cost, bool checkFlag) : cour(cour), prev(0), cost(cost), checkFlag(checkFlag){}
	Nodesp() :cour(0), prev(0), cost(1.e30), checkFlag(false), checked(false){}
};

std::pair<double, std::vector<int>> compute_sp(int origin, int dest, std::vector<int> path, const  Params & params);

#endif
