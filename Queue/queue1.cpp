#include <iostream>
#include <string>
using namespace std;

#define MAX 1000

class AppointmentQueue {
    int front, rear, size;
    string queue[MAX];   // storing patient names or appointment IDs

public:
    AppointmentQueue() {
        front = size = 0;
        rear = MAX - 1;
    }

    bool isFull() {
        return (size == MAX);
    }

    bool isEmpty() {
        return (size == 0);
    }

    // Add appointment to the back of the queue
    void addAppointment(string patient) {
        if (isFull()) {
            cout << "Appointment queue is full!" << endl;
            return;
        }
        rear = (rear + 1) % MAX;
        queue[rear] = patient;
        size++;
        cout << "Appointment added for: " << patient << endl;
    }

    // Serve patient from the front (FCFS)
    string serveAppointment() {
        if (isEmpty()) {
            cout << "No appointments to serve!" << endl;
            return "";
        }
        string patient = queue[front];
        front = (front + 1) % MAX;
        size--;
        return patient;
    }

    // Reinsert a rescheduled patient at the correct position (end of queue)
    void rescheduleAppointment(string patient) {
        cout << "Rescheduling appointment for: " << patient << endl;
        addAppointment(patient); // place at back without disturbing order
    }

    void printQueue() {
        if (isEmpty()) {
            cout << "No appointments in the queue!" << endl;
            return;
        }

        cout << "Current Appointment Queue: ";
        for (int i = front, count = 0; count < size; count++) {
            cout << queue[i] << " | ";
            i = (i + 1) % MAX;
        }
        cout << endl;
    }
};

int main() {
    AppointmentQueue aq;
    int choice;
    string name;

    while (1) {
        cout << "\n--- Appointment Management Menu ---\n";
        cout << "1. Add Appointment\n";
        cout << "2. Serve Appointment\n";
        cout << "3. Reschedule Appointment\n";
        cout << "4. Show All Appointments\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            cout << "Enter patient name: ";
            cin >> name;
            aq.addAppointment(name);
            break;

        case 2:
            name = aq.serveAppointment();
            if (name != "")
                cout << "Serving: " << name << endl;
            break;

        case 3:
            cout << "Enter patient name to reschedule: ";
            cin >> name;
            aq.rescheduleAppointment(name);
            break;

        case 4:
            aq.printQueue();
            break;

        case 5:
            cout << "Exiting...\n";
            return 0;

        default:
            cout << "Invalid choice. Try again!\n";
        }
    }
}
