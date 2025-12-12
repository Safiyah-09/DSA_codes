#include <iostream>
using namespace std;

int n, dataArray[100], BIT[100];

class Fenwick {
public:
    Fenwick(int n);
    void buildTree();
    void update(int index, int value);
    int prefixSum(int index);
    int rangeSum(int left, int right);
};

Fenwick::Fenwick(int n) {
    for (int i = 0; i <= n; i++) {
        BIT[i] = 0;
    }
}

// Build the BIT for daily hospital statistics
void Fenwick::buildTree() {
    cout << "Enter daily statistics (patients/bills/tests):\n";
    for (int i = 1; i <= n; i++) {
        cin >> dataArray[i];
        update(i, dataArray[i]); // insert into BIT
    }
}

// Update daily counts like new patients or new tests
void Fenwick::update(int index, int value) {
    while (index <= n) {
        BIT[index] += value;
        index += index & -index; // move to parent
    }
}

// Get cumulative total up to a specific day
int Fenwick::prefixSum(int index) {
    int result = 0;
    while (index > 0) {
        result += BIT[index];
        index -= index & -index; // move to previous node
    }
    return result;
}

// Get total of any date range (start → end)
int Fenwick::rangeSum(int left, int right) {
    return prefixSum(right) - prefixSum(left - 1);
}

int main() {
    cout << "Enter number of days to track hospital analytics: ";
    cin >> n;

    Fenwick hospitalBIT(n);
    hospitalBIT.buildTree();

    int start, end;
    cout << "Enter range (start day and end day) to get total analytics: ";
    cin >> start >> end;

    cout << "Total count in this range = "
         << hospitalBIT.rangeSum(start, end) << endl;

    return 0;
}
