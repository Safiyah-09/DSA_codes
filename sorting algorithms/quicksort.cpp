#include <iostream>
#include <string>
using namespace std;

struct Product {
    string name;
    int category;  // we sort based on this (category/size)
};

// Partition function customized for Product sorting
int Partition(Product A[], int l, int r) {
    Product pivot = A[l]; 
    int i = l;
    int j = r + 1;

    while (true) {
        // Move i right
        do {
            i++;
        } while (i <= r && A[i].category <= pivot.category);

        // Move j left
        do {
            j--;
        } while (A[j].category > pivot.category);

        if (i >= j)
            break;

        swap(A[i], A[j]);
    }

    swap(A[l], A[j]);  // place pivot correctly
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

    cout << "Enter product name and category(size code):\n";
    for (int i = 0; i < n; i++) {
        cout << "Product " << i + 1 << " name: ";
        cin >> A[i].name;
        cout << "Category/Size code (numeric): ";
        cin >> A[i].category;
    }

    // Sort products for optimized shelf arrangement
    QuickSort(A, 0, n - 1);

    // Display shelf arrangement
    cout << "\nShelf-arranged product order (sorted by category/size):\n";
    for (int i = 0; i < n; i++) {
        cout << A[i].name << " (Category: " << A[i].category << ")\n";
    }

    return 0;
}
