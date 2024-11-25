#include "Genetic.h"
#include "commandline.h"
#include "LocalSearch.h"
#include "Split.h"
#include "InstanceCVRPLIB.h"
//#include <./../../spStruct.h>

//#include "dllmain.h"

using namespace std;

int main(int argc, char *argv[])
//int main()
{
	//In the case one wants to call the program from the code instead of the command prompt
	int argc1 = 9;
	char** mystr=  new char* [argc1];
	mystr[1] = const_cast <char*>("Golden/Golden_1-C25-N241.gvrp");	
	mystr[2] = const_cast <char*>("mySolution.sol");
	mystr[3] = const_cast <char*>("-seed");
	mystr[4] = const_cast <char*>("2");
	mystr[5] = const_cast <char*>("-t");
	mystr[6] = const_cast <char*>("10");
	mystr[7] = const_cast <char*>("-cluvrp");
	mystr[8] = const_cast <char*>("1");
	try
	{
		// Reading the arguments of the program
		//Reading from the prompt
		CommandLine commandline(argc, argv);
		//Reading from the parameters set in the previous lines
		//CommandLine commandline(argc1, mystr);
		// Print all algorithm parameter values
		if (commandline.verbose) print_algorithm_parameters(commandline.ap);
		// Reading the data file and initializing some data structures
		if (commandline.verbose) std::cout << "----- READING INSTANCE: " << commandline.pathInstance << std::endl;
		
		InstanceCVRPLIB cvrp(commandline.pathInstance, commandline.isRoundingInteger,commandline.cluvrp, true);
		//for (int seed = 1; seed <= 10; seed++)
		//{


			//VVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVV
			//Commands for performing multiple runs without recreating every time the instance 
			//commandline.ap.seed = seed;
			//commandline.ap.nbIter =  1.e7;
			//commandline.ap.timeLimit = cvrp.n_nodes * 2.4;

			


			//VVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVV
			Params params(cvrp.x_coords, cvrp.y_coords, cvrp.dist_mtx, cvrp.service_time, cvrp.demands,
				cvrp.vehicleCapacity, cvrp.durationLimit, cvrp.real_nbVeh, cvrp.isDurationConstraint, commandline.verbose, commandline.ap, cvrp.depot, cvrp.arcs, cvrp.arcscluster, cvrp.dist_mtxN);

			// Running HGS
			Genetic solver(params);
			solver.run();
			


			// Exporting the best solution
			if (solver.population.getBestFound() != NULL)
			{
				if (params.verbose) std::cout << "----- WRITING BEST SOLUTION IN : " << commandline.pathSolution << std::endl;
				//std::cout << "FO: " << indiv.indiv.eval.penalizedCost << std::endl;
				solver.population.exportCVRPLibFormat(*solver.population.getBestFound(), commandline.pathSolution);
				solver.population.exportSearchProgress(commandline.pathSolution + ".PG.csv", commandline.pathInstance);
			}


		//}
	}
	catch (const string& e) { std::cout << "EXCEPTION | " << e << std::endl; }
	catch (const std::exception& e) { std::cout << "EXCEPTION | " << e.what() << std::endl; }
	return 0;
}

