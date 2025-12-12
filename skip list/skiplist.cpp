#include <iostream>
#include <cstdlib>
#include <cmath>
#include <string>
using namespace std;

#define MAX_LEVEL 5   // Number of levels in Skip List
#define P 0.5         // Probability factor

// -----------------------------
// Patient Node
// -----------------------------
struct Node {
    string name;
    int priority; // 1 = high (emergency), 2 = low (normal)
    Node** forward;
    Node(int level, string name, int priority) {
        this->name = name;
        this->priority = priority;
        forward = new Node*[level + 1];
        for (int i = 0; i <= level; i++)
            forward[i] = nullptr;
    }
};

// -----------------------------
// Skip List Class
// -----------------------------
class SkipList {
private:
    int level;
    Node* header;

public:
    SkipList() {
        level = 0;
        header = new Node(MAX_LEVEL, "", 0);
    }

    // Random level generator
    int randomLevel() {
        int lvl = 0;
        while ((double)rand() / RAND_MAX < P && lvl < MAX_LEVEL)
            lvl++;
        return lvl;
    }

    // Insert patient by priority
    void insertPatient(string name, int priority) {
        Node* current = header;
        Node* update[MAX_LEVEL + 1];

        for (int i = level; i >= 0; i--) {
            while (current->forward[i] != nullptr &&
                   current->forward[i]->priority <= priority) {
                current = current->forward[i];
            }
            update[i] = current;
        }

        int newLevel = randomLevel();

        if (newLevel > level) {
            for (int i = level + 1; i <= newLevel; i++)
                update[i] = header;
            level = newLevel;
        }

        Node* newNode = new Node(newLevel, name, priority);

        for (int i = 0; i <= newLevel; i++) {
            newNode->forward[i] = update[i]->forward[i];
            update[i]->forward[i] = newNode;
        }

        cout << "Inserted Patient: " << name
             << " (Priority: " << priority << ")" << endl;
    }

    // Doctor picks highest priority patient (front node)
    void servePatient() {
        if (header->forward[0] == nullptr) {
            cout << "No patients in queue.\n";
            return;
        }

        Node* first = header->forward[0];
        cout << "Doctor is treating: " << first->name
             << " (Priority: " << first->priority << ")\n";

        // Remove the node from all levels
        for (int i = 0; i <= level; i++) {
            if (header->forward[i] != first)
                break;
            header->forward[i] = first->forward[i];
        }

        delete first;
    }

    // View skip list (optional)
    void display() {
        cout << "\nSkip List (Priority Queue):\n";
        for (int i = 0; i <= level; i++) {
            Node* node = header->forward[i];
            cout << "Level " << i << ": ";
            while (node) {
                cout << "(" << node->name << ", P:" << node->priority << ") ";
                node = node->forward[i];
            }
            cout << endl;
        }
    }
};

// -----------------------------
// MAIN
// -----------------------------
int main() {
    SkipList sl;

    sl.insertPatient("John", 2);      // Normal
    sl.insertPatient("Emma", 1);      // Emergency
    sl.insertPatient("Mia", 2);
    sl.insertPatient("Raj", 1);       // Emergency

    sl.display();

    cout << "\n--- Doctor Calling Patients ---\n";
    sl.servePatient();  // should pick Emma (priority 1)
    sl.servePatient();  // should pick Raj (priority 1)
    sl.servePatient();  // normal patients next

    return 0;
}
