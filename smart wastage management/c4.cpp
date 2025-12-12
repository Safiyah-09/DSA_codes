#include <iostream>
#include <queue>
using namespace std;

/* ============================================================
   BINARY TREE — Store bin metadata for fast dashboard lookup
   ============================================================ */

struct BinNode {
    int binID;
    string location;
    string lastUpdate; 
    BinNode *left, *right;

    BinNode(int id, string loc, string update) {
        binID = id;
        location = loc;
        lastUpdate = update;
        left = right = NULL;
    }
};

BinNode* insertBT(BinNode* root, int id, string loc, string update) {
    if (!root) return new BinNode(id, loc, update);

    if (id < root->binID)
        root->left = insertBT(root->left, id, loc, update);
    else
        root->right = insertBT(root->right, id, loc, update);

    return root;
}

void searchBin(BinNode* root, int id) {
    if (!root) return;

    if (root->binID == id) {
        cout << "\nBin Found:\n";
        cout << "ID: " << root->binID << "\n";
        cout << "Location: " << root->location << "\n";
        cout << "Last Update: " << root->lastUpdate << "\n";
        return;
    }

    if (id < root->binID) searchBin(root->left, id);
    else searchBin(root->right, id);
}

/* ============================================================
   DFS — Scan all bins zone-by-zone to detect faulty bins
   ============================================================ */

int visitedDFS[20];

void dfs(int graph[20][20], int v, int source) {
    visitedDFS[source] = 1;

    cout << "Scanning Bin " << source << "...\n";

    for (int i = 0; i < v; i++) {
        if (graph[source][i] == 1 && visitedDFS[i] == 0) {
            dfs(graph, v, i);
        }
    }
}

/* ============================================================
   BFS — Find the nearest bin with issues (for dashboard alerts)
   ============================================================ */

void bfs(int graph[20][20], int v, int source, int issueBin) {
    int visited[20] = {0};
    queue<int> q;

    q.push(source);
    visited[source] = 1;

    cout << "\nFinding nearest bin with issues...\n";

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        if (u == issueBin) {
            cout << "Nearest Problematic Bin Found: Bin " << u << "\n";
            return;
        }

        for (int i = 0; i < v; i++) {
            if (graph[u][i] == 1 && visited[i] == 0) {
                visited[i] = 1;
                q.push(i);
            }
        }
    }

    cout << "No problematic bin found nearby.\n";
}

/* ============================================================
   MAIN
   ============================================================ */

int main() {
    int v = 6;

    // Graph showing connections between bins
    int graph[20][20] = {
        {0,1,1,0,0,0},
        {1,0,0,1,1,0},
        {1,0,0,0,0,1},
        {0,1,0,0,0,0},
        {0,1,0,0,0,0},
        {0,0,1,0,0,0}
    };

    // -------------------- Binary Tree Setup --------------------
    BinNode* root = NULL;

    root = insertBT(root, 0, "Zone A", "10:05 AM");
    root = insertBT(root, 1, "Zone B", "10:10 AM");
    root = insertBT(root, 2, "Zone C", "10:02 AM");
    root = insertBT(root, 3, "Zone D", "9:59 AM");
    root = insertBT(root, 4, "Zone E", "10:11 AM");
    root = insertBT(root, 5, "Zone F", "10:00 AM");

    // -------------------- DFS Scan --------------------
    cout << "\n==== Zone-by-Zone DFS Scan ====\n";
    for (int i = 0; i < v; i++) visitedDFS[i] = 0;

    dfs(graph, v, 0);

    // -------------------- BFS for Nearest Problem Bin --------------------
    int problemBin;
    cout << "\nEnter problematic bin ID to locate nearest: ";
    cin >> problemBin;

    bfs(graph, v, 0, problemBin);

    // -------------------- Binary Tree Lookup --------------------
    int searchID;
    cout << "\nEnter bin ID to view details: ";
    cin >> searchID;

    searchBin(root, searchID);

    return 0;
}
