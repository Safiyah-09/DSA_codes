#include <iostream>
#include <string>
using namespace std;

// Product structure
struct Product {
    string name;
    int expiryDays;   // Number of days until expiry
};

// Partition function for QuickSort (sorting by expiryDays)
int Partition(Product A[], int l, int r) {
    Product pivot = A[l]; // first product as pivot
    int i = l;
    int j = r + 1;

    while (true) {
        // Move i to the right until you find a product with expiry >= pivot
        do {
            i++;
        } while (i <= r && A[i].expiryDays <= pivot.expiryDays);

        // Move j to the left until you find a product with expiry <= pivot
        do {
            j--;
        } while (A[j].expiryDays > pivot.expiryDays);

        if (i >= j)
            break;

        // Swap products at i and j
        swap(A[i], A[j]);
    }

    // Place pivot in correct position
    swap(A[l], A[j]);

    return j;
}

// QuickSort function
void QuickSort(Product A[], int l, int r) {
    if (l < r) {
        int s = Partition(A, l, r);

        QuickSort(A, l, s - 1);
        QuickSort(A, s + 1, r);
    }
}

int main() {
    int n;

    cout << "Enter number of products: ";
    cin >> n;

    Product A[n];

    // Input products
    cout << "\nEnter product details:\n";
    for (int i = 0; i < n; i++) {
        cout << "\nProduct " << i + 1 << " name: ";
        cin >> A[i].name;

        cout << "Days until expiry: ";
        cin >> A[i].expiryDays;
    }

    // Sort by expiry (QuickSort)
    QuickSort(A, 0, n - 1);

    // Display sorted shelf arrangement
    cout << "\n=== Shelf Arrangement (Soon-to-expire first) ===\n";
    for (int i = 0; i < n; i++) {
        cout << A[i].name << " — " << A[i].expiryDays << " days left\n";
    }

    return 0;
}
