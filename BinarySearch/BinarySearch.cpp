#include <iostream>
using namespace std;

// Structure for each patient node
struct Patient {
    int id;
    string name;
    Patient* left;
    Patient* right;

    Patient(int patientID, string patientName) {
        id = patientID;
        name = patientName;
        left = right = nullptr;
    }
};

// Insert a new patient into BST
Patient* insertPatient(Patient* root, int id, string name) {
    if (root == nullptr) {
        return new Patient(id, name);
    }

    if (id < root->id) {
        root->left = insertPatient(root->left, id, name);
    }
    else if (id > root->id) {
        root->right = insertPatient(root->right, id, name);
    }

    return root;
}

// Search for a patient using ID
Patient* searchPatient(Patient* root, int key) {
    if (root == nullptr || root->id == key)
        return root;

    if (key < root->id)
        return searchPatient(root->left, key);
    else
        return searchPatient(root->right, key);
}

int main() {
    int n;
    cout << "Enter number of patients: ";
    cin >> n;

    Patient* root = nullptr;

    // Insert patient records
    for (int i = 0; i < n; i++) {
        int id;
        string name;
        cout << "Enter Patient ID and Name: ";
        cin >> id >> name;

        root = insertPatient(root, id, name);
    }

    // Search a patient by ID
    int key;
    cout << "Enter Patient ID to search: ";
    cin >> key;

    Patient* result = searchPatient(root, key);

    if (result != nullptr) {
        cout << "Patient Found!" << endl;
        cout << "ID: " << result->id << ", Name: " << result->name << endl;
    } 
    else {
        cout << "Patient not found." << endl;
    }

    return 0;
}
