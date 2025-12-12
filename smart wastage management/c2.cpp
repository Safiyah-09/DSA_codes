#include <iostream>
using namespace std;

/* --------------------------------------------------------
   SECTION 1: DFS – Explore all road paths between bins
   -------------------------------------------------------- */

int V = 5; // Number of bins/intersections
int roadMap[10][10] = {
    {0,1,1,0,0},
    {1,0,0,1,1},
    {1,0,0,0,1},
    {0,1,0,0,0},
    {0,1,1,0,0}
};

int visitedDFS[10];

void DFS(int graph[10][10], int v, int source) {
    visitedDFS[source] = 1;

    for (int i = 0; i < v; i++) {
        if (graph[source][i] == 1 && visitedDFS[i] == 0) {
            cout << " -> Bin " << i;
            DFS(graph, v, i);
        }
    }
}

/* --------------------------------------------------------
   SECTION 2: BFS – Find nearest bin from truck location
   -------------------------------------------------------- */

void BFS(int graph[10][10], int v, int source) {
    int queue[20];
    int front = 0, rear = 0, u, i;
    int visited[10];

    for (i = 0; i < v; i++)
        visited[i] = 0;

    queue[rear] = source;
    visited[source] = 1;

    cout << "\nShortest hop-based route from Truck at Bin " << source << ":\n";

    while (front <= rear) {
        u = queue[front];
        cout << "Bin " << u << " ";
        front++;

        for (i = 0; i < v; i++) {
            if (graph[u][i] == 1 && visited[i] == 0) {
                visited[i] = 1;
                rear++;
                queue[rear] = i;
            }
        }
    }
}

/* --------------------------------------------------------
   SECTION 3: KRUSKAL – Create MST for optimal route grouping
   -------------------------------------------------------- */

int findSet(int arr[], int u, int v) {
    return arr[u] == arr[v];
}

void unionSet(int arr[], int n, int u, int v) {
    int temp = arr[u];
    for (int i = 0; i < n; i++)
        if (arr[i] == temp)
            arr[i] = arr[v];
}

int Partition(int A[], int B[], int C[], int l, int r) {
    int pivot = A[l], pivotB = B[l], pivotC = C[l];
    int i = l, j = r + 1;

    while (true) {
        do { i++; } while (i <= r && A[i] <= pivot);
        do { j--; } while (A[j] > pivot);

        if (i >= j) break;

        swap(A[i], A[j]);
        swap(B[i], B[j]);
        swap(C[i], C[j]);
    }

    swap(A[l], A[j]);
    swap(B[l], B[j]);
    swap(C[l], C[j]);

    return j;
}

void QuickSort(int A[], int B[], int C[], int l, int r) {
    if (l < r) {
        int s = Partition(A, B, C, l, r);
        QuickSort(A, B, C, l, s - 1);
        QuickSort(A, B, C, s + 1, r);
    }
}

void Kruskal(int n, int e, int u[], int v[], int w[]) {
    int setArr[n];
    for (int i = 0; i < n; i++)
        setArr[i] = i;

    int mstCost = 0;

    QuickSort(w, u, v, 0, e - 1);

    cout << "\nOptimized Waste Collection Path (MST):\n";
    for (int i = 0; i < e; i++) {
        if (!findSet(setArr, u[i], v[i])) {
            unionSet(setArr, n, u[i], v[i]);
            mstCost += w[i];
            cout << "Bin " << u[i] << " ↔ Bin " << v[i]
                 << " (Road distance: " << w[i] << ")\n";
        }
    }

    cout << "Total optimized route cost = " << mstCost << "\n";
}

/* --------------------------------------------------------
   MAIN PROGRAM
   -------------------------------------------------------- */

int main() {
    int source;

    // ---------------- DFS ----------------
    for (int i = 0; i < V; i++)
        visitedDFS[i] = 0;

    cout << "Enter starting bin for full route exploration (DFS): ";
    cin >> source;

    cout << "\nDFS Exploration of Road Network:\nBin " << source;
    DFS(roadMap, V, source);


    // ---------------- BFS ----------------
    cout << "\n\nEnter truck's current bin to find nearest bins (BFS): ";
    cin >> source;

    BFS(roadMap, V, source);


    // ---------------- KRUSKAL (MST) ----------------
    int e;
    cout << "\n\nEnter number of road segments for MST: ";
    cin >> e;

    int u[e], v[e], w[e];
    cout << "Enter road connections (bin1 bin2 distance):\n";
    for (int i = 0; i < e; i++)
        cin >> u[i] >> v[i] >> w[i];

    Kruskal(V, e, u, v, w);

    return 0;
}
