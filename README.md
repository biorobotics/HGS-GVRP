

# HGS-GVRP: An adaption of the Hybrid Genetic Search for the GVRP

This is a implementation of the Hybrid Genetic Search (HGS), specialized to the Generalized Vehicle Routing Problem (GVRP). 
The code is obtained making the necessary changes to the original code by Thibaut Vidal available on https://github.com/vidalt/HGS-CVRP

This algorithm has been designed to maintain the efficiency of the original code, only changing the elements to adapt it to the GVRP

## References

When using this algorithm (or part of it) in derived academic studies, please refer to the following works:

[1] Latorre, V.(2024). 
A Hybrid Genetic Search Based Approach for the Generalized Vehicle Routing Problem. Accepted for Soft Computing. 

I also recommend referring to the Github version of the code used.

## Scope

This code has been designed to solve a problem in the family of the Capacitated Vehicle Routing Problem (CVRP), the Generalized VRP. 
The GVRP is a generalization of the CVRP where the nodes are divided into clusters and just one node must be visited per cluster.
Like the original algorithm, it should also be able to directly handle asymmetric distances as well as duration constraints.

This code version has been tested up to medium-scale instances with 1,200 customers. 

I have included a Windows compiled .exe and a batch file that calls all the instances problems in the class Golden1. 
The .exe has been created in Visual Studio 2022, it should also compile in other enviroments but I did not test it

The following options are supported:
```
Call with: ./hgs instancePath solPath [-it nbIter] [-t myCPUtime] [-bks bksPath] [-seed mySeed] [-veh nbVehicles] [-log verbose]
[-it <int>] sets a maximum number of iterations without improvement. Defaults to 20,000                                     
[-t <double>] sets a time limit in seconds. If this parameter is set, the code will be run iteratively until the time limit           
[-seed <int>] sets a fixed seed. Defaults to 0                                                                                    
[-veh <int>] sets a prescribed fleet size. Otherwise a reasonable UB on the fleet size is calculated                      
[-round <bool>] rounding the distance to the nearest integer or not. It can be 0 (not rounding) or 1 (rounding). Defaults to 1. 
[-log <bool>] sets the verbose level of the algorithm log. It can be 0 or 1. Defaults to 1.                                       

Additional Arguments:
[-nbIterTraces <int>] Number of iterations between traces display during HGS execution. Defaults to 500
[-nbGranular <int>] Granular search parameter, limits the number of moves in the RI local search. Defaults to 20               
[-mu <int>] Minimum population size. Defaults to 25                                                                            
[-lambda <int>] Number of solutions created before reaching the maximum population size (i.e., generation size). Defaults to 40
[-nbElite <int>] Number of elite individuals. Defaults to 5                                                                    
[-nbClose <int>] Number of closest solutions/individuals considered when calculating diversity contribution. Defaults to 4     
[-nbIterPenaltyManagement <int>] Number of iterations between penalty updates. Defaults to 100
[-targetFeasible <double>] target ratio of feasible individuals between penalty updates. Defaults to 0.2
[-penaltyIncrease <double>] penalty increase if insufficient feasible individuals between penalty updates. Defaults to 1.2
[-penaltyDecrease <double>] penalty decrease if sufficient feasible individuals between penalty updates. Defaults to 0.85
[-cluvrp <bool>] sets the kind of file. 1 indicates that the file is in the form of CluVRP instances with the cost of hamiltonian 
		 paths reported in the file. 0 indicates that it is a GVRP problem. Defaults to 0
```

There exist different conventions regarding distance calculations in the academic literature.
The default code behavior is to apply integer rounding, as it should be done on the X instances of Uchoa et al. (2017).
To change this behavior (e.g., when testing on the CMT or Golden instances), give a flag `-round 0`, when you run the executable.

The progress of the algorithm in the standard output will be displayed as:

``
It [N1] [N2] | T(s) [T] | Feas [NF] [BestF] [AvgF] | Inf [NI] [BestI] [AvgI] | Div [DivF] [DivI] | Feas [FeasC] [FeasD] | Pen [PenC] [PenD]
``
```
[N1] and [N2]: Total number of iterations and iterations without improvement
[T]: CPU time spent until now
[NF] and [NI]: Number of feasible and infeasible solutions in the subpopulations 
[BestF] and [BestI]: Value of the best feasible and infeasible solution in the subpopulations 
[AvgF] and [AvgI]: Average value of the solutions in the feasible and infeasible subpopulations 
[DivF] and [DivI]: Diversity of the feasible and infeasible subpopulations
[FC] and [FD]: Percentage of naturally feasible solutions in relation to the capacity and duration constraints
[PC] and [PD]: Current penalty level per unit of excess capacity and duration
```

## Code structure

The main classes containing the logic of the algorithm are the following:
* **Params**: Stores the main data structures for the method
* **Individual**: Represents an individual solution in the genetic algorithm, also provides I/O functions to read and write individual solutions in CVRPLib format.
* **Population**: Stores the solutions of the genetic algorithm into two different groups according to their feasibility. Also includes the functions in charge of diversity management.
* **Genetic**: Contains the main procedures of the genetic algorithm as well as the crossover
* **LocalSearch**: Includes the local search functions, including the SWAP* neighborhood
* **Split**: Algorithms designed to decode solutions represented as giant tours into complete CVRP solutions
* **CircleSector**: Small code used to represent and manage arc sectors (to efficiently restrict the SWAP* neighborhood)
* **short_path**: It computes the customer visits in shortest path a vehicle has to traverse starting from the depot, going through the given a sequence of clusters and back to the depot

In addition, additional classes have been created to facilitate interfacing:
* **AlgorithmParameters**: Stores the parameters of the algorithm
* **CVRPLIB** Contains the instance data and functions designed to read input data as text files according to the CVRPLIB conventions
* **commandline**: Reads the line of command
* **main**: Main code to start the algorithm



## License

[![License](http://img.shields.io/:license-mit-blue.svg?style=flat-square)](http://badges.mit-license.org)

- **[MIT license](http://opensource.org/licenses/mit-license.php)**
- Copyright(c) 2024 Vittorio Latorre
