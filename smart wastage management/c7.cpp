#include <iostream>
#include <queue>
#include <cmath>
using namespace std;

// =====================================================
// BINARY TREE – Store bin/truck GPS coordinates
// =====================================================
struct BTNode {
    int id;             // bin or truck ID
    float lat, lon;     // GPS coordinates
    BTNode *left, *right;

    BTNode(int i, float la, float lo) {
        id = i; lat = la; lon = lo;
        left = right = NULL;
    }
};

BTNode* insertBT(BTNode* root, int id, float lat, float lon) {
    if (!root) return new BTNode(id, lat, lon);

    if (id < root->id)
        root->left = insertBT(root->left, id, lat, lon);
    else
        root->right = insertBT(root->right, id, lat, lon);

    return root;
}

void displayBT(BTNode* root) {
    if (!root) return;
    displayBT(root->left);
    cout << "ID " << root->id << " → (" << root->lat << ", " << root->lon << ")\n";
    displayBT(root->right);
}


// =====================================================
// 2–3 TREE – Handle continuous GPS updates
// =====================================================
struct TTNode {
    float val1, val2;          // store lat-lon pairs (flattened value)
    bool twoValues;
    TTNode *left, *mid, *right;

    TTNode(float v) {
        val1 = v;
        twoValues = false;
        val2 = -1;
        left = mid = right = NULL;
    }
};

TTNode* insert23(TTNode* root, float val) {
    if (!root) return new TTNode(val);

    if (val < root->val1)
        root->left = insert23(root->left, val);
    else if (!root->twoValues) {
        root->val2 = val;
        root->twoValues = true;
    }
    else
        root->mid = insert23(root->mid, val);

    return root;
}

void display23(TTNode* root) {
    if (!root) return;
    display23(root->left);
    cout << "GPS Update Value: " << root->val1 << "\n";
    if (root->twoValues)
        cout << "GPS Update Value: " << root->val2 << "\n";
    display23(root->mid);
    display23(root->right);
}


// =====================================================
// BFS – Find nearest bin to truck in grid
// =====================================================
int rows = 5, cols = 5;
int grid[5][5] = {
    {0,1,0,0,0},
    {0,0,0,1,0},
    {1,0,0,0,1},
    {0,0,1,0,0},
    {0,0,0,0,0}
};

int dr[4] = {1,-1,0,0};
int dc[4] = {0,0,1,-1};

bool isValid(int r, int c) {
    return (r >= 0 && r < rows && c >= 0 && c < cols);
}

void BFS_findNearestBin(int startR, int startC) {
    queue<pair<int,int>> q;
    bool visited[5][5] = {false};

    q.push({startR, startC});
    visited[startR][startC] = true;

    cout << "\nBFS Search Path from Truck Location:\n";

    while (!q.empty()) {
        auto [r, c] = q.front();
        q.pop();

        cout << "(" << r << "," << c << ") ";

        if (grid[r][c] == 1) {
            cout << "\nNearest Bin Found at (" << r << "," << c << ")\n";
            return;
        }

        for (int i = 0; i < 4; i++) {
            int nr = r + dr[i];
            int nc = c + dc[i];

            if (isValid(nr, nc) && !visited[nr][nc]) {
                visited[nr][nc] = true;
                q.push({nr, nc});
            }
        }
    }

    cout << "\nNo bin found.\n";
}


// =====================================================
// MAIN FUNCTION
// =====================================================
int main() {

    BTNode* gpsTree = NULL;
    TTNode* gpsUpdates = NULL;

    // Insert bin & truck locations into Binary Tree
    gpsTree = insertBT(gpsTree, 1, 12.97, 77.59); // Bin
    gpsTree = insertBT(gpsTree, 2, 12.98, 77.60); // Bin
    gpsTree = insertBT(gpsTree, 3, 12.96, 77.61); // Truck
    gpsTree = insertBT(gpsTree, 4, 12.95, 77.58); // Bin

    cout << "===== Binary Tree: Bin/Truck Locations =====\n";
    displayBT(gpsTree);

    // Insert GPS updates into 2–3 Tree
    gpsUpdates = insert23(gpsUpdates, 77.5912);
    gpsUpdates = insert23(gpsUpdates, 77.6020);
    gpsUpdates = insert23(gpsUpdates, 77.6150);

    cout << "\n===== 2–3 Tree: Continuous GPS Updates =====\n";
    display23(gpsUpdates);

    // BFS to find nearest bin to truck
    cout << "\n===== BFS: Find Nearest Bin to Truck =====\n";
    BFS_findNearestBin(2, 2);  // Truck starting location in grid

    return 0;
}
