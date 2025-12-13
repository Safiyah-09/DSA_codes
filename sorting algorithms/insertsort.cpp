#include <iostream>
#include <string>
using namespace std;

// Structure to store dish details
struct Dish {
    string name;
    int rating;    // Popularity or rating score
};

// Insertion Sort (Descending Order)
void insertionSort(Dish dishes[], int n) {
    for (int i = 1; i < n; i++) {
        Dish key = dishes[i];
        int j = i - 1;

        // Move smaller ratings one position ahead
        while (j >= 0 && dishes[j].rating < key.rating) {
            dishes[j + 1] = dishes[j];
            j--;
        }
        dishes[j + 1] = key;
    }
}

// Display Top-N recommended dishes
void displayTopN(Dish dishes[], int n, int topN) {
    cout << "\nTop " << topN << " Recommended Dishes:\n";
    for (int i = 0; i < topN && i < n; i++) {
        cout << dishes[i].name << " (Rating: " << dishes[i].rating << ")\n";
    }
}

int main() {
    Dish dishes[] = {
        {"Pizza", 5},
        {"Burger", 4},
        {"Pasta", 3},
        {"Sandwich", 4},
        {"Biryani", 5}
    };

    int n = sizeof(dishes) / sizeof(dishes[0]);
    int topN;

    insertionSort(dishes, n);

    cout << "Enter number of top recommendations: ";
    cin >> topN;

    displayTopN(dishes, n, topN);

    return 0;
}
