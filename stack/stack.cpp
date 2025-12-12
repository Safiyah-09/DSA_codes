#include <iostream>
using namespace std;
#define MAX 1000

class EmergencyStack {
    int top;
    string stack[MAX];   // store patient names or IDs

public:
    EmergencyStack() {
        top = -1;
    }

    bool isFull() {
        return top == MAX - 1;
    }

    bool isEmpty() {
        return top == -1;
    }

    // Add a new emergency patient
    void push(string patient) {
        if (isFull()) {
            cout << "Emergency Stack is full!" << endl;
            return;
        }
        stack[++top] = patient;
        cout << "Emergency case added: " << patient << endl;
    }

    // Doctor treats the most recent emergency
    string pop() {
        if (isEmpty()) {
            cout << "No emergency patients!" << endl;
            return "";
        }
        string patient = stack[top--];
        return patient;
    }

    // View all emergency patients
    void printStack() {
        if (isEmpty()) {
            cout << "No emergency patients in stack!" << endl;
            return;
        }
        cout << "Current Emergency Stack: ";
        for (int i = top; i >= 0; i--) {
            cout << stack[i] << " ";
        }
        cout << endl;
    }
};

int main() {
    EmergencyStack es;
    int choice;
    string name;

    while (true) {
        cout << "\n--- Emergency Handling Menu ---\n";
        cout << "1. Add Emergency Patient\n";
        cout << "2. Treat Emergency Patient\n";
        cout << "3. View Emergency Stack\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            cout << "Enter emergency patient name: ";
            cin >> name;
            es.push(name);
            break;

        case 2:
            name = es.pop();
            if (name != "")
                cout << "Treated emergency patient: " << name << endl;
            break;

        case 3:
            es.printStack();
            break;

        case 4:
            cout << "Exiting...\n";
            return 0;

        default:
            cout << "Invalid choice. Try again.\n";
        }
    }
}
