#include <iostream>
#include <string>
using namespace std;

const int SIZE = 10;   // hash table size

// Product structure
struct Product {
    string name;
    int quantity;
    int minLevel;
    int maxLevel;
};

// Hash Table (simple)
Product hashTable[SIZE];

// Hash function
int hashFunction(string key) {
    int sum = 0;
    for (char c : key)
        sum += c;
    return sum % SIZE;
}

// Insert product into hash table
void insertProduct(string name, int qty, int minL, int maxL) {
    int index = hashFunction(name);

    // Linear probing for collision
    while (hashTable[index].name != "") {
        index = (index + 1) % SIZE;
    }

    hashTable[index].name = name;
    hashTable[index].quantity = qty;
    hashTable[index].minLevel = minL;
    hashTable[index].maxLevel = maxL;

    cout << "Product added: " << name << endl;
}

// Check stock status
void checkStock(string name) {
    int index = hashFunction(name);

    // Search using linear probing
    int start = index;
    bool found = false;

    while (hashTable[index].name != "") {
        if (hashTable[index].name == name) {
            found = true;

            int qty = hashTable[index].quantity;
            int minL = hashTable[index].minLevel;
            int maxL = hashTable[index].maxLevel;

            cout << "\nProduct: " << name << " | Quantity: " << qty << endl;

            if (qty < minL)
                cout << "⚠ UNDERSTOCK ALERT! Needs Reorder.\n";
            else if (qty > maxL)
                cout << "⚠ OVERSTOCK ALERT! Reduce Stock.\n";
            else
                cout << "Stock Level: OK\n";

            return;
        }

        index = (index + 1) % SIZE;
        if (index == start) break;
    }

    if (!found)
        cout << "Product not found in inventory.\n";
}

// Update stock levels
void updateStock(string name, int newQty) {
    int index = hashFunction(name);
    int start = index;

    while (hashTable[index].name != "") {
        if (hashTable[index].name == name) {
            hashTable[index].quantity = newQty;
            cout << "\nStock updated for " << name << endl;
            checkStock(name);
            return;
        }

        index = (index + 1) % SIZE;
        if (index == start) break;
    }

    cout << "Product not found.\n";
}

int main() {
    int n;
    cout << "Enter number of products: ";
    cin >> n;

    for (int i = 0; i < n; i++) {
        string name;
        int qty, minL, maxL;

        cout << "\nEnter product name: ";
        cin >> name;

        cout << "Enter quantity: ";
        cin >> qty;

        cout << "Enter minimum level (reorder point): ";
        cin >> minL;

        cout << "Enter maximum level (overstock limit): ";
        cin >> maxL;

        insertProduct(name, qty, minL, maxL);
    }

    // Stock checking
    string checkItem;
    cout << "\nEnter product name to check stock: ";
    cin >> checkItem;
    checkStock(checkItem);

    // Update stock example
    string updateItem;
    int newQty;

    cout << "\nEnter product name to update quantity: ";
    cin >> updateItem;

    cout << "Enter new quantity: ";
    cin >> newQty;

    updateStock(updateItem, newQty);

    return 0;
}
