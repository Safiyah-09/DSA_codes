#include <iostream>
#include <string>
using namespace std;

#define MAX 1000

class CheckoutQueue {
    int front, rear, size;
    string queue[MAX];

public:
    CheckoutQueue() {
        front = size = 0;
        rear = MAX - 1;
    }

    bool isFull() {
        return (size == MAX);
    }

    bool isEmpty() {
        return (size == 0);
    }

    void enqueue(string customer) {
        if (isFull()) {
            cout << "Queue is full. Cannot add more customers." << endl;
            return;
        }

        rear = (rear + 1) % MAX;
        queue[rear] = customer;
        size++;

        cout << "Customer " << customer << " joined the checkout queue." << endl;

        // Auto-open counter when queue grows large
        if (size > 5) {
            cout << "Queue is long. Opening an additional billing counter." << endl;
        }
    }

    string dequeue() {
        if (isEmpty()) {
            cout << "No customers in queue." << endl;
            return "";
        }

        string customer = queue[front];
        front = (front + 1) % MAX;
        size--;

        return customer;
    }

    void printQueue() {
        if (isEmpty()) {
            cout << "No customers are currently waiting." << endl;
            return;
        }

        cout << "Current checkout queue: ";
        for (int i = front, count = 0; count < size; count++) {
            cout << queue[i] << " ";
            i = (i + 1) % MAX;
        }
        cout << endl;
    }
};

int main() {
    CheckoutQueue q;
    int choice;
    string name;

    while (true) {
        cout << "\nCheckout Menu:\n";
        cout << "1. Customer Arrives (Enqueue)\n";
        cout << "2. Serve Customer (Dequeue)\n";
        cout << "3. Show Queue\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter customer name: ";
                cin >> name;
                q.enqueue(name);
                break;

            case 2: {
                string served = q.dequeue();
                if (served != "") {
                    cout << "Serving customer: " << served << endl;
                }
                break;
            }

            case 3:
                q.printQueue();
                break;

            case 4:
                cout << "Exiting checkout system..." << endl;
                return 0;

            default:
                cout << "Invalid choice. Try again." << endl;
        }
    }

    return 0;
}
