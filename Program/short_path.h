

#ifndef short_path
#define short_path

#include "vector" 
#include "./Params.h"


std::pair<double, std::vector<int>> compute_sp(int origin, int dest, std::vector<int> path, const  Params & params);

#endif