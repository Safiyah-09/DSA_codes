#include <iostream>
using namespace std;

// -----------------------------
// Binary Tree for Current Waste
// -----------------------------
struct BTNode {
    int zoneID;
    int wasteLevel; 
    BTNode *left, *right;

    BTNode(int id, int w) {
        zoneID = id;
        wasteLevel = w;
        left = right = NULL;
    }
};

BTNode* insertBT(BTNode* root, int id, int w) {
    if (!root) return new BTNode(id, w);

    if (w < root->wasteLevel)
        root->left = insertBT(root->left, id, w);
    else
        root->right = insertBT(root->right, id, w);

    return root;
}

void inorderDisplay(BTNode* root) {
    if (!root) return;
    inorderDisplay(root->left);
    cout << "Zone " << root->zoneID 
         << " | Current Waste: " << root->wasteLevel << "\n";
    inorderDisplay(root->right);
}

// -----------------------------
// Simplified 2–3 Tree Node
// -----------------------------
struct TTNode {
    int val1, val2;   // two values
    bool twoValues;   // tells if node has 2 keys
    TTNode *left, *mid, *right;

    TTNode(int v) {
        val1 = v;
        twoValues = false;
        val2 = -1;
        left = mid = right = NULL;
    }
};

// Insert into simplified 2–3 Tree
TTNode* insert23(TTNode* root, int val) {
    if (!root) return new TTNode(val);

    if (val < root->val1) {
        root->left = insert23(root->left, val);
    } else if (!root->twoValues) {
        root->val2 = val;
        root->twoValues = true;
    } else {
        root->mid = insert23(root->mid, val);
    }
    return root;
}

void display23(TTNode* root) {
    if (!root) return;
    display23(root->left);

    cout << "Historical Waste Pattern: " << root->val1 << "\n";
    if (root->twoValues)
        cout << "Historical Waste Pattern: " << root->val2 << "\n";

    display23(root->mid);
    display23(root->right);
}

// -----------------------------
// Allocation Logic
// -----------------------------
void allocateTrucks(BTNode* root) {
    if (!root) return;
    allocateTrucks(root->left);

    cout << "Zone " << root->zoneID << " Allocation → ";
    if (root->wasteLevel > 70)
        cout << "High Priority: 3 Trucks + 4 Staff\n";
    else if (root->wasteLevel > 40)
        cout << "Medium Priority: 2 Trucks + 2 Staff\n";
    else
        cout << "Low Priority: 1 Truck + 1 Staff\n";

    allocateTrucks(root->right);
}

// -----------------------------
// MAIN
// -----------------------------
int main() {

    BTNode* currentWaste = NULL;
    TTNode* historicalWaste = NULL;

    // Sample zone data
    currentWaste = insertBT(currentWaste, 1, 35);
    currentWaste = insertBT(currentWaste, 2, 80);
    currentWaste = insertBT(currentWaste, 3, 55);
    currentWaste = insertBT(currentWaste, 4, 15);

    // Historical load patterns (2–3 tree)
    historicalWaste = insert23(historicalWaste, 40);
    historicalWaste = insert23(historicalWaste, 60);
    historicalWaste = insert23(historicalWaste, 75);
    historicalWaste = insert23(historicalWaste, 50);

    cout << "\n===== CURRENT WASTE LEVELS (Binary Tree) =====\n";
    inorderDisplay(currentWaste);

    cout << "\n===== HISTORICAL WASTE PATTERNS (2–3 Tree) =====\n";
    display23(historicalWaste);

    cout << "\n===== TRUCK & STAFF ALLOCATION =====\n";
    allocateTrucks(currentWaste);

    return 0;
}
