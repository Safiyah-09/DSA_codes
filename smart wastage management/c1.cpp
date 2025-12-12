#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

/* ============================================================
   BINARY TREE  
   → Stores bin fill levels in sorted order
   → Helps quickly find bins that are nearing overflow
============================================================ */

struct BinNode {
    int fillLevel;
    BinNode* left;
    BinNode* right;

    BinNode(int level) : fillLevel(level), left(NULL), right(NULL) {}
};

BinNode* insertBinFill(BinNode* root, int level) {
    if (!root) return new BinNode(level);

    if (level < root->fillLevel)
        root->left = insertBinFill(root->left, level);
    else
        root->right = insertBinFill(root->right, level);

    return root;
}

// Display sorted bin fill levels
void displayBinTree(BinNode* root) {
    if (!root) return;
    displayBinTree(root->left);
    cout << root->fillLevel << " ";
    displayBinTree(root->right);
}

/* ============================================================
   SIMPLE 2–3 TREE SIMULATION   
   → Stores continuous sensor readings
   → Maintains balanced sorted structure
   → Fast overflow detection
============================================================ */

class TwoThreeTree {
public:
    vector<int> readings;

    void insertReading(int value) {
        readings.push_back(value);
        sort(readings.begin(), readings.end());
    }

    void showReadings() {
        cout << "Sensor Readings (2–3 Tree): ";
        for (int r : readings) cout << r << " ";
        cout << endl;
    }
};

/* ============================================================
   BUBBLE SORT  
   → Sort bins by fill level (high → low)
   → Highlights nearly overflowing bins at the top
============================================================ */

void bubbleSortBins(vector<int>& bins) {
    int n = bins.size();
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (bins[j] < bins[j + 1]) {
                swap(bins[j], bins[j + 1]);
            }
        }
    }
}

/* ============================================================
   MAIN — DEMONSTRATION OF ALL ADS WORKING TOGETHER
============================================================ */

int main() {

    cout << "\n=== Smart Waste System: Overflowing Bins Detection ===\n";

    /* -------------------- Binary Tree -------------------- */
    cout << "\nBinary Tree (Sorted Fill Levels): ";
    BinNode* root = NULL;
    vector<int> fillLevels = {45, 80, 95, 60, 30, 88};

    for (int level : fillLevels)
        root = insertBinFill(root, level);

    displayBinTree(root);


    /* -------------------- 2–3 Tree -------------------- */
    cout << "\n\nContinuous Sensor Readings (2–3 Tree):\n";
    TwoThreeTree sensorTree;
    vector<int> readings = {50, 92, 63, 70, 88};

    for (int r : readings)
        sensorTree.insertReading(r);

    sensorTree.showReadings();


    /* -------------------- Bubble Sort -------------------- */
    cout << "\nBins Sorted by Fill Level (High → Low): ";
    bubbleSortBins(fillLevels);

    for (int val : fillLevels)
        cout << val << " ";


    cout << "\n\nSystem Processing Completed.\n";

    return 0;
}
