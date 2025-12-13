#include <iostream>
#define MAX 100
#define INF 999
using namespace std;

class DeliveryNetwork {
public:
    int locations;
    int dist[MAX][MAX];

    DeliveryNetwork(int n);
    void readDistances();
    void displayDistances();
    void computeAllPairsShortestPath();
};

DeliveryNetwork::DeliveryNetwork(int n) {
    locations = n;
}

// Read distance / travel-time matrix
void DeliveryNetwork::readDistances() {
    cout << "Enter distance matrix (use 999 for no direct route):\n";
    for (int i = 1; i <= locations; i++) {
        for (int j = 1; j <= locations; j++) {
            cin >> dist[i][j];
        }
    }
}

// Display matrix
void DeliveryNetwork::displayDistances() {
    for (int i = 1; i <= locations; i++) {
        for (int j = 1; j <= locations; j++) {
            if (dist[i][j] == INF)
                cout << "INF\t";
            else
                cout << dist[i][j] << "\t";
        }
        cout << endl;
    }
}

// Floyd–Warshall Algorithm
void DeliveryNetwork::computeAllPairsShortestPath() {
    for (int k = 1; k <= locations; k++) {
        for (int i = 1; i <= locations; i++) {
            for (int j = 1; j <= locations; j++) {
                if (dist[i][k] != INF && dist[k][j] != INF &&
                    dist[i][k] + dist[k][j] < dist[i][j]) {
                    dist[i][j] = dist[i][k] + dist[k][j];
                }
            }
        }
    }
}

int main() {
    int n;
    cout << "Enter number of delivery locations: ";
    cin >> n;

    DeliveryNetwork network(n);

    network.readDistances();

    cout << "\nInitial Distance Matrix:\n";
    network.displayDistances();

    network.computeAllPairsShortestPath();

    cout << "\nShortest Distance Between All Delivery Locations:\n";
    network.displayDistances();

    return 0;
}
