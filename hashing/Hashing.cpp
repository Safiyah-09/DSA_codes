#include <iostream>
#include <string>
using namespace std;

const int TABLE_SIZE = 10;

// Node for storing product info
struct Node {
    int sku;            // product ID
    string name;        // product name
    int quantity;       // stock level
    Node* next;

    Node(int s, string n, int q) {
        sku = s;
        name = n;
        quantity = q;
        next = NULL;
    }
};

class HashTable {
private:
    Node* table[TABLE_SIZE];

    int hashFunction(int key) {
        return key % TABLE_SIZE;
    }

public:
    HashTable() {
        for (int i = 0; i < TABLE_SIZE; ++i)
            table[i] = NULL;
    }

    // Insert new product OR update existing product quantity
    void insert(int sku, string name, int quantity) {
        int index = hashFunction(sku);
        Node* newNode = new Node(sku, name, quantity);

        if (table[index] == NULL) {
            table[index] = newNode;
        } else {
            Node* temp = table[index];

            while (temp->next != NULL) {
                // Update existing product
                if (temp->sku == sku) {
                    temp->quantity = quantity;
                    temp->name = name;
                    delete newNode;
                    return;
                }
                temp = temp->next;
            }

            // Last node check
            if (temp->sku == sku) {
                temp->quantity = quantity;
                temp->name = name;
                delete newNode;
                return;
            }

            // Insert new product in chain
            temp->next = newNode;
        }
    }

    // Search for a product by SKU
    void search(int sku) {
        int index = hashFunction(sku);
        Node* temp = table[index];

        while (temp != NULL) {
            if (temp->sku == sku) {
                cout << "\nProduct Found:\n";
                cout << "SKU: " << temp->sku << endl;
                cout << "Name: " << temp->name << endl;
                cout << "Quantity: " << temp->quantity << endl;
                return;
            }
            temp = temp->next;
        }

        cout << "Product not found in inventory.\n";
    }

    // Remove a product from inventory
    void removeProduct(int sku) {
        int index = hashFunction(sku);
        Node* temp = table[index];
        Node* prev = NULL;

        while (temp != NULL && temp->sku != sku) {
            prev = temp;
            temp = temp->next;
        }

        if (temp == NULL) {
            cout << "Product not found.\n";
            return;
        }

        if (prev == NULL)
            table[index] = temp->next;
        else
            prev->next = temp->next;

        delete temp;
        cout << "Product removed successfully.\n";
    }
};

int main() {
    HashTable inventory;
    int choice, sku, qty;
    string name;

    do {
        cout << "\n--- Supermarket Inventory Menu ---\n";
        cout << "1. Add/Update Product\n";
        cout << "2. Search Product\n";
        cout << "3. Remove Product\n";
        cout << "4. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            cout << "Enter SKU: ";
            cin >> sku;
            cout << "Enter Product Name: ";
            cin >> name;
            cout << "Enter Quantity: ";
            cin >> qty;
            inventory.insert(sku, name, qty);
            break;

        case 2:
            cout << "Enter SKU to Search: ";
            cin >> sku;
            inventory.search(sku);
            break;

        case 3:
            cout << "Enter SKU to Remove: ";
            cin >> sku;
            inventory.removeProduct(sku);
            break;

        case 4:
            cout << "Exiting Inventory System...\n";
            break;

        default:
            cout << "Invalid choice. Try again.\n";
        }

    } while (choice != 4);

    return 0;
}
