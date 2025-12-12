#include <iostream>
using namespace std;

/* ============================================================
   BINARY TREE — Store alert thresholds & rules
   ============================================================ */

struct AlertNode {
    int threshold;
    AlertNode *left, *right;

    AlertNode(int t) {
        threshold = t;
        left = right = NULL;
    }
};

AlertNode* insertAlert(AlertNode* root, int t) {
    if (!root) return new AlertNode(t);

    if (t < root->threshold)
        root->left = insertAlert(root->left, t);
    else
        root->right = insertAlert(root->right, t);

    return root;
}

bool checkAlert(AlertNode* root, int value) {
    if (!root) return false;

    if (value >= root->threshold)
        return true;

    if (value < root->threshold)
        return checkAlert(root->left, value);
    
    return checkAlert(root->right, value);
}

/* ============================================================
   SIMPLE 2–3 TREE SIMULATION — Store real-time sensor values
   ============================================================ */

struct TwoThreeNode {
    int data1, data2;
    bool isTwoNode; 
    TwoThreeNode *left, *middle, *right;

    TwoThreeNode(int val) {
        data1 = val;
        data2 = -1;
        isTwoNode = true;
        left = middle = right = NULL;
    }
};

TwoThreeNode* insert23(TwoThreeNode* root, int val) {
    if (!root) return new TwoThreeNode(val);

    if (val < root->data1) {
        root->left = insert23(root->left, val);
    } 
    else if (root->isTwoNode) {
        root->data2 = val;
        root->isTwoNode = false;
    }
    else {
        root->right = insert23(root->right, val);
    }

    return root;
}

void inorder23(TwoThreeNode* root) {
    if (!root) return;

    inorder23(root->left);
    cout << root->data1 << " ";
    if (!root->isTwoNode) cout << root->data2 << " ";
    inorder23(root->middle);
    inorder23(root->right);
}

/* ============================================================
   BUBBLE SORT — Sort bins by fill level (High → Low)
   ============================================================ */

void bubbleSort(int bins[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (bins[j] < bins[j + 1]) {  // High → Low
                swap(bins[j], bins[j + 1]);
            }
        }
    }
}

/* ============================================================
   MAIN PROGRAM
   ============================================================ */

int main() {
    int n;
    cout << "Enter number of bins: ";
    cin >> n;

    int bins[50];
    cout << "Enter fill levels of bins (%):\n";
    for (int i = 0; i < n; i++)
        cin >> bins[i];

    // ---------------------------------------------------------
    // BUBBLE SORT — Bring dangerous bins to top
    // ---------------------------------------------------------
    bubbleSort(bins, n);

    cout << "\nSorted bins from High → Low:\n";
    for (int i = 0; i < n; i++)
        cout << bins[i] << " ";
    cout << endl;

    // ---------------------------------------------------------
    // 2–3 TREE — Insert real-time sensor values
    // ---------------------------------------------------------
    TwoThreeNode* sensorRoot = NULL;
    for (int i = 0; i < n; i++)
        sensorRoot = insert23(sensorRoot, bins[i]);

    cout << "\n2–3 Tree Sensor Values (Inorder): ";
    inorder23(sensorRoot);
    cout << endl;

    // ---------------------------------------------------------
    // BINARY TREE — Store alert thresholds
    // ---------------------------------------------------------
    AlertNode* alertRoot = NULL;
    alertRoot = insertAlert(alertRoot, 70);  // Danger threshold
    alertRoot = insertAlert(alertRoot, 85);  // Severe level

    // ---------------------------------------------------------
    // CHECK FOR ALERTS
    // ---------------------------------------------------------
    cout << "\nChecking alerts...\n";
    for (int i = 0; i < n; i++) {
        if (checkAlert(alertRoot, bins[i])) {
            cout << "ALERT! Bin with " << bins[i] 
                 << "% fill has crossed the threshold!\n";
        }
    }

    return 0;
}
