#include "short_path.h"

using namespace std;


std::pair<double, std::vector<int>> dijkstra(vector<int> path, int origin, int dest, const std::vector<std::vector<std::vector<std::vector<double>>>>& arcscluster, const int& nnodes) {
    std::vector < Nodesp > clients(nnodes+1);
    double cost;
    for (int i = 0; i < arcscluster[0][path[origin]].size(); i++)
    {
        clients[arcscluster[0][path[origin]][i][1]].cour= arcscluster[0][path[origin]][i][1];
        clients[arcscluster[0][path[origin]][i][1]].cost= arcscluster[0][path[origin]][i][2];
    }
    for (int i = origin; i <= dest - 1; i++)
    {
        int n_tail = arcscluster[0][path[i]].size();
        int n_head = arcscluster[0][path[i + 1]].size();
        for (int k = 0; k < n_head; k++) {
            clients[arcscluster[0][path[i + 1]][k][1]].cour = arcscluster[0][path[i + 1]][k][1];
            clients[arcscluster[0][path[i + 1]][k][1]].cost = 1.e30;
        }
        for (int jj = 0; jj < arcscluster[path[i]][path[i + 1]].size(); ++jj) //for all the nodes in the tail cluster
            {
            cost = clients[arcscluster[path[i]][path[i + 1]][jj][0]].cost + arcscluster[path[i]][path[i + 1]][jj][2];
            if (cost < clients[arcscluster[path[i]][path[i + 1]][jj][1]].cost)
                {
                    clients[arcscluster[path[i]][path[i + 1]][jj][1]].cost = cost;
                    clients[arcscluster[path[i]][path[i + 1]][jj][1]].prev = clients[arcscluster[path[i]][path[i + 1]][jj][0]].cour;
                }
            }
    }
    //Last round for the depot
    Nodesp depot;
    depot.cost = 1.e30;
    for (int i = 0; i < arcscluster[path[dest]][0].size(); i++)
    {
        cost = clients[arcscluster[path[dest]][0][i][0]].cost + arcscluster[path[dest]][0][i][2];
        if (cost < depot.cost)
        {
            depot.cost = cost;
            depot.prev = clients[arcscluster[path[dest]][0][i][0]].cour;
        }
    }
    //recosctruct the path from the end
    std::vector<int> node_path = std::vector<int>(path.size());
    node_path[path.size() - 1] = clients[depot.prev].cour;
    for (int i = path.size() - 2; i >= 0; i--)
    {
        node_path[i] = clients[node_path[i + 1]].prev;
    }

    return std::make_pair(depot.cost, node_path);
}


std::pair<double, std::vector<int>> compute_sp(int origin, int dest, vector<int> path, const Params & params) {
    //
    std::pair<double, std::vector<int>> dist = dijkstra(path, origin, dest, params.arcscluster,params.depot);

    return dist; 
}
