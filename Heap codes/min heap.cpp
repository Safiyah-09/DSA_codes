#include <iostream>
#include <string>
using namespace std;

struct Product {
    string name;
    int expiry; // number of days left before expiry
};

class MinHeap {
private:
    Product heap[100];
    int size;

    // Swap two products
    void swap(Product &a, Product &b) {
        Product temp = a;
        a = b;
        b = temp;
    }

    // Move element up to maintain heap property
    void heapifyUp(int index) {
        while (index > 0 && heap[(index - 1) / 2].expiry > heap[index].expiry) {
            swap(heap[(index - 1) / 2], heap[index]);
            index = (index - 1) / 2;
        }
    }

    // Move element down to maintain heap property
    void heapifyDown(int index) {
        int left = 2 * index + 1;
        int right = 2 * index + 2;
        int smallest = index;

        if (left < size && heap[left].expiry < heap[smallest].expiry)
            smallest = left;

        if (right < size && heap[right].expiry < heap[smallest].expiry)
            smallest = right;

        if (smallest != index) {
            swap(heap[smallest], heap[index]);
            heapifyDown(smallest);
        }
    }

public:
    MinHeap() {
        size = 0;
    }

    // Insert product into the heap
    void insertProduct(string name, int expiry) {
        Product p;
        p.name = name;
        p.expiry = expiry;

        heap[size] = p;
        heapifyUp(size);
        size++;

        cout << name << " added to expiry tracking.\n";
    }

    // Get product closest to expiry
    void getSoonToExpire() {
        if (size == 0) {
            cout << "No products available.\n";
            return;
        }

        cout << "\nProduct expiring soonest:\n";
        cout << "Name: " << heap[0].name << "\n";
        cout << "Days left: " << heap[0].expiry << "\n";

        if (heap[0].expiry <= 2) {
            cout << "⚠ ALERT: This item is about to expire! Apply discount or remove soon.\n";
        }
    }
};

int main() {
    MinHeap mh;
    int choice;
    string name;
    int expiry;

    do {
        cout << "\n--- Soon-to-Expire Product Tracker (Min-Heap) ---\n";
        cout << "1. Add Product\n";
        cout << "2. View Soonest Expiring Product\n";
        cout << "3. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            cout << "Enter product name: ";
            cin >> name;
            cout << "Enter days left to expire: ";
            cin >> expiry;
            mh.insertProduct(name, expiry);
            break;

        case 2:
            mh.getSoonToExpire();
            break;

        case 3:
            cout << "Exiting...\n";
            break;

        default:
            cout << "Invalid choice.\n";
        }

    } while (choice != 3);

    return 0;
}
