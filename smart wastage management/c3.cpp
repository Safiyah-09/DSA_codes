#include <iostream>
using namespace std;

/* ================================================================
   SECTION 1: BINARY TREE – Store historical data and compare trends
   ================================================================= */

struct BTNode {
    int date;       // store date as number (1–365)
    int wasteLevel; // waste level in kg
    BTNode *left, *right;

    BTNode(int d, int w) {
        date = d;
        wasteLevel = w;
        left = right = NULL;
    }
};

BTNode* insertBT(BTNode* root, int date, int wasteLevel) {
    if (!root)
        return new BTNode(date, wasteLevel);

    if (date < root->date)
        root->left = insertBT(root->left, date, wasteLevel);
    else
        root->right = insertBT(root->right, date, wasteLevel);

    return root;
}

void checkSpike(BTNode* root, int currentWaste) {
    if (!root) return;

    checkSpike(root->left, currentWaste);

    if (root->wasteLevel < currentWaste)
        cout << "Past date " << root->date 
             << " had lower waste (" << root->wasteLevel 
             << "), current spike detected!\n";

    checkSpike(root->right, currentWaste);
}

/* ================================================================
   SECTION 2: 2–3 TREE – Balanced Tree for trend analysis
   ================================================================= */

struct TTNode {
    int data1, data2;        // store waste levels
    TTNode *left, *mid, *right;
    bool twoNode;            // TRUE = 2-node, FALSE = 3-node

    TTNode(int val) {
        data1 = val;
        data2 = -1;
        left = mid = right = NULL;
        twoNode = true;
    }
};

TTNode* insert23(TTNode* root, int val) {
    if (!root) return new TTNode(val);

    // Insert into a 2-node
    if (root->twoNode) {
        if (val < root->data1) {
            root->data2 = root->data1;
            root->data1 = val;
        } else {
            root->data2 = val;
        }
        root->twoNode = false;    // becomes 3-node
        return root;
    }

    // Insert into a 3-node (simple split simulation)
    if (!root->twoNode) {
        int small = min(val, min(root->data1, root->data2));
        int large = max(val, max(root->data1, root->data2));
        int middle = root->data1 + root->data2 + val - small - large;

        // Split node (very simplified logic)
        root->data1 = middle;
        root->data2 = -1;
        root->twoNode = true;

        // Create children
        root->left = new TTNode(small);
        root->mid = new TTNode(large);

        return root;
    }

    return root;
}

void findHighWasteDays(TTNode* root, int threshold) {
    if (!root) return;

    if (root->left) findHighWasteDays(root->left, threshold);

    if (root->data1 >= threshold)
        cout << "High waste level detected: " << root->data1 << "\n";
    if (!root->twoNode && root->data2 >= threshold)
        cout << "High waste level detected: " << root->data2 << "\n";

    if (root->mid) findHighWasteDays(root->mid, threshold);
    if (root->right) findHighWasteDays(root->right, threshold);
}

/* ================================================================
   MAIN PROGRAM
   ================================================================= */

int main() {
    BTNode* btRoot = NULL;
    TTNode* t23Root = NULL;

    int n, date, waste;

    cout << "Enter number of historical records: ";
    cin >> n;

    cout << "Enter historical data (date wasteLevel):\n";
    for (int i = 0; i < n; i++) {
        cin >> date >> waste;

        btRoot = insertBT(btRoot, date, waste);   // insert in Binary Tree
        t23Root = insert23(t23Root, waste);      // insert only waste level in 2-3 tree
    }

    int currentWaste;
    cout << "\nEnter today's waste level: ";
    cin >> currentWaste;

    cout << "\n---- Checking Spike using Binary Tree ----\n";
    checkSpike(btRoot, currentWaste);

    cout << "\n---- High Waste Days (Festival Pattern) using 2–3 Tree ----\n";
    findHighWasteDays(t23Root, currentWaste);

    return 0;
}
