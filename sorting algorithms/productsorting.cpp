#include <iostream>
#include <vector>
#include <string>
using namespace std;

struct Product {
    string name;
    float price;
    int rating;
    int expiryDays;
};

// ------------------ MERGESORT (Sort by Price) ------------------

void merge(vector<Product>& arr, int left, int mid, int right) {
    vector<Product> temp;
    int i = left, j = mid + 1;

    while (i <= mid && j <= right) {
        if (arr[i].price <= arr[j].price)
            temp.push_back(arr[i++]);
        else
            temp.push_back(arr[j++]);
    }

    while (i <= mid) temp.push_back(arr[i++]);
    while (j <= right) temp.push_back(arr[j++]);

    for (int k = left, t = 0; k <= right; k++, t++)
        arr[k] = temp[t];
}

void mergeSort(vector<Product>& arr, int left, int right) {
    if (left < right) {
        int mid = (left + right) / 2;
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}

// ------------------ HEAPSORT (Sort by Rating) ------------------

void heapify(vector<Product>& arr, int n, int i) {
    int largest = i;
    int left = 2*i + 1;
    int right = 2*i + 2;

    if (left < n && arr[left].rating > arr[largest].rating)
        largest = left;

    if (right < n && arr[right].rating > arr[largest].rating)
        largest = right;

    if (largest != i) {
        swap(arr[i], arr[largest]);
        heapify(arr, n, largest);
    }
}

void heapSort(vector<Product>& arr) {
    int n = arr.size();

    // Build heap
    for (int i = n/2 - 1; i >= 0; i--)
        heapify(arr, n, i);

    // Extract elements
    for (int i = n - 1; i > 0; i--) {
        swap(arr[0], arr[i]);
        heapify(arr, i, 0);
    }
}

// ------------------ QUICKSORT (Sort by Expiry Days) ------------------

int partitionQS(vector<Product>& arr, int low, int high) {
    int pivot = arr[low].expiryDays;
    int i = low;
    int j = high + 1;

    while (true) {
        do { i++; } while (i <= high && arr[i].expiryDays <= pivot);
        do { j--; } while (arr[j].expiryDays > pivot);

        if (i >= j) break;
        swap(arr[i], arr[j]);
    }

    swap(arr[low], arr[j]);
    return j;
}

void quickSort(vector<Product>& arr, int low, int high) {
    if (low < high) {
        int pi = partitionQS(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

// ------------------ UTILITY FUNCTIONS ------------------

void printProducts(const vector<Product>& arr) {
    cout << "\nProduct List:\n";
    for (auto& p : arr) {
        cout << p.name << " | Price: " << p.price 
             << " | Rating: " << p.rating 
             << " | Expiry (days): " << p.expiryDays << endl;
    }
}

int main() {
    int n;
    cout << "Enter number of products: ";
    cin >> n;

    vector<Product> products(n);

    cout << "Enter product details:\n";
    for (int i = 0; i < n; i++) {
        cout << "\nProduct " << i+1 << " Name: ";
        cin >> products[i].name;
        cout << "Price: ";
        cin >> products[i].price;
        cout << "Rating (1-5): ";
        cin >> products[i].rating;
        cout << "Expiry in days: ";
        cin >> products[i].expiryDays;
    }

    int choice;
    cout << "\nChoose sorting method:\n";
    cout << "1. Sort by Price (MergeSort)\n";
    cout << "2. Sort by Rating (HeapSort)\n";
    cout << "3. Sort by Expiry Date (QuickSort)\n";
    cout << "Enter choice: ";
    cin >> choice;

    switch (choice) {
        case 1:
            mergeSort(products, 0, n - 1);
            cout << "\nSorted by Price:\n";
            break;

        case 2:
            heapSort(products);
            cout << "\nSorted by Rating:\n";
            break;

        case 3:
            quickSort(products, 0, n - 1);
            cout << "\nSorted by Expiry Days:\n";
            break;

        default:
            cout << "Invalid choice!";
            return 0;
    }

    printProducts(products);
    return 0;
}
