#include <iostream>
#include <string>
using namespace std;

struct Product {
    string name;
    int sales;  // priority (max-heap uses highest sales on top)
};

class MaxHeap {
private:
    Product heap[100];
    int size;

    void swap(Product &a, Product &b) {
        Product temp = a;
        a = b;
        b = temp;
    }

    void heapifyUp(int index) {
        while (index > 1 && heap[index].sales > heap[index / 2].sales) {
            swap(heap[index], heap[index / 2]);
            index /= 2;
        }
    }

    void heapifyDown(int index) {
        int largest = index;
        int left = index * 2;
        int right = index * 2 + 1;

        if (left <= size && heap[left].sales > heap[largest].sales)
            largest = left;

        if (right <= size && heap[right].sales > heap[largest].sales)
            largest = right;

        if (largest != index) {
            swap(heap[index], heap[largest]);
            heapifyDown(largest);
        }
    }

public:
    MaxHeap() {
        size = 0;
    }

    void insertProduct(string name, int sales) {
        size++;
        heap[size].name = name;
        heap[size].sales = sales;

        heapifyUp(size);

        cout << "Product added: " << name << " | Sales: " << sales << endl;
    }

    void recordSale(string name) {
        for (int i = 1; i <= size; i++) {
            if (heap[i].name == name) {
                heap[i].sales++;
                cout << "Sale recorded for " << name << endl;
                heapifyUp(i);
                return;
            }
        }
        cout << "Product not found!" << endl;
    }

    void showBestSeller() {
        if (size == 0) {
            cout << "No products available." << endl;
            return;
        }

        cout << "Best Selling Product:" << endl;
        cout << "Product: " << heap[1].name 
             << " | Sales: " << heap[1].sales << endl;
    }

    void displayHeap() {
        cout << "Current Heap (Product : Sales):" << endl;
        for (int i = 1; i <= size; i++) {
            cout << heap[i].name << " : " << heap[i].sales << endl;
        }
    }
};

int main() {
    MaxHeap h;

    int n;
    cout << "Enter number of products: ";
    cin >> n;

    for (int i = 0; i < n; i++) {
        string name;
        int sales;
        cout << "Enter product name: ";
        cin >> name;
        cout << "Enter initial sales count: ";
        cin >> sales;

        h.insertProduct(name, sales);
    }

    h.showBestSeller();

    int s;
    cout << "Enter number of sales to record: ";
    cin >> s;

    while (s--) {
        string pname;
        cout << "Enter product sold: ";
        cin >> pname;

        h.recordSale(pname);
        h.showBestSeller();
    }

    cout << "Final Heap Status:" << endl;
    h.displayHeap();

    return 0;
}
