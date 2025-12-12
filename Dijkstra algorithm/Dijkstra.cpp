#include <iostream>
#include <algorithm>
using namespace std;

class DijkstraHospital
{
public:
    int parent[4];       // Stores path (previous room)
    int distance[4];     // Stores shortest distance from source
    int visited[4];      // Marks visited rooms

    void initialize(int cost[4][4], int source);
    int getMinNode();
    void updatePaths(int cost[4][4]);
    void computeShortestRoute(int cost[4][4], int source);
    void displayRoutes(int source);
};

void DijkstraHospital::initialize(int cost[4][4], int source)
{
    for (int i = 0; i < 4; i++)
    {
        parent[i] = source;

        // If no direct path → consider as very large distance
        distance[i] = (cost[source][i] == 0 ? 10000000 : cost[source][i]);
        visited[i] = 0;
    }

    visited[source] = 1;
    distance[source] = 0;
}

int DijkstraHospital::getMinNode()
{
    int minVal = 10000000;
    int index = -1;

    for (int i = 0; i < 4; i++)
    {
        if (!visited[i] && distance[i] < minVal)
        {
            minVal = distance[i];
            index = i;
        }
    }
    return index;
}

void DijkstraHospital::updatePaths(int cost[4][4])
{
    int u = getMinNode();
    if (u == -1)
        return;

    visited[u] = 1;

    for (int i = 0; i < 4; i++)
    {
        if (!visited[i])
        {
            int newDist = distance[u] + cost[u][i];
            if (newDist < distance[i])
            {
                distance[i] = newDist;
                parent[i] = u;
            }
        }
    }
}

void DijkstraHospital::computeShortestRoute(int cost[4][4], int source)
{
    initialize(cost, source);
    for (int i = 0; i < 3; i++)
        updatePaths(cost);
}

void DijkstraHospital::displayRoutes(int source)
{
    cout << "\n--- Shortest Routes Inside Hospital ---\n";

    for (int i = 0; i < 4; i++)
    {
        if (i != source)
        {
            cout << "Fastest route from room " << source << " to room " << i
                 << " = distance " << distance[i] << "\nPath: ";

            int j = i;
            cout << j;

            while (parent[j] != source)
            {
                cout << " <- " << parent[j];
                j = parent[j];
            }

            cout << " <- " << source << endl << endl;
        }
    }
}

int main()
{
    int source;
    int cost[4][4];

    cout << "Enter starting room (source): ";
    cin >> source;

    cout << "Enter hospital distance/time matrix (4x4):\n";
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            cin >> cost[i][j];
        }
    }

    DijkstraHospital hospital;
    hospital.computeShortestRoute(cost, source);
    hospital.displayRoutes(source);

    return 0;
}
