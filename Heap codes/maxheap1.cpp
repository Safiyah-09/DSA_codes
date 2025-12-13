#include <iostream>
#include <string>
using namespace std;

#define MAX 10   // Maximum number of dishes

// Structure to store dish details
struct Dish {
    string name;
    int orders;     // Frequency count
};

// Max-Heap class
class MaxHeap {
    Dish heap[MAX];
    int size;

public:
    MaxHeap() {
        size = 0;
    }

    // Swap two dishes
    void swap(Dish &a, Dish &b) {
        Dish temp = a;
        a = b;
        b = temp;
    }

    // Heapify upwards
    void heapifyUp(int index) {
        int parent = (index - 1) / 2;
        if (index > 0 && heap[index].orders > heap[parent].orders) {
            swap(heap[index], heap[parent]);
            heapifyUp(parent);
        }
    }

    // Heapify downwards
    void heapifyDown(int index) {
        int largest = index;
        int left = 2 * index + 1;
        int right = 2 * index + 2;

        if (left < size && heap[left].orders > heap[largest].orders)
            largest = left;
        if (right < size && heap[right].orders > heap[largest].orders)
            largest = right;

        if (largest != index) {
            swap(heap[index], heap[largest]);
            heapifyDown(largest);
        }
    }

    // Insert or update dish order count
    void addOrder(string dishName) {
        // Check if dish already exists
        for (int i = 0; i < size; i++) {
            if (heap[i].name == dishName) {
                heap[i].orders++;
                heapifyUp(i);
                return;
            }
        }

        // Insert new dish
        heap[size] = {dishName, 1};
        heapifyUp(size);
        size++;
    }

    // Display most popular dish
    void showTrending() {
        if (size == 0) {
            cout << "No orders yet.\n";
            return;
        }
        cout << "\nMost Ordered Dish:\n";
        cout << heap[0].name << " (Orders: " << heap[0].orders << ")\n";
    }

    // Extract most popular dish
    void extractMax() {
        if (size == 0) {
            cout << "Heap is empty.\n";
            return;
        }

        cout << "\nExtracted Trending Dish:\n";
        cout << heap[0].name << " (Orders: " << heap[0].orders << ")\n";

        heap[0] = heap[size - 1];
        size--;
        heapifyDown(0);
    }
};

// Main function
int main() {
    MaxHeap trending;
    int choice;
    string dish;

    while (true) {
        cout << "\nTrending Dishes Menu\n";
        cout << "1. Add Order\n";
        cout << "2. Show Most Ordered Dish\n";
        cout << "3. Extract Trending Dish\n";
        cout << "4. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            cin.ignore();
            cout << "Enter dish name: ";
            getline(cin, dish);
            trending.addOrder(dish);
            cout << "Order added successfully.\n";
            break;

        case 2:
            trending.showTrending();
            break;

        case 3:
            trending.extractMax();
            break;

        case 4:
            cout << "Exiting system.\n";
            return 0;

        default:
            cout << "Invalid choice.\n";
        }
    }
}
