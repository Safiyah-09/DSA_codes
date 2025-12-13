#include <iostream>
using namespace std;

// Structure for Order
struct Order {
    int orderID;          // Can also be timestamp
    string customerName;
    Order* left;
    Order* right;
    int height;
};

// Get height of node
int height(Order* node) {
    if (node == NULL)
        return 0;
    return node->height;
}

// Get balance factor
int getBalance(Order* node) {
    if (node == NULL)
        return 0;
    return height(node->left) - height(node->right);
}

// Create new order node
Order* createOrder(int id, string name) {
    Order* newNode = new Order();
    newNode->orderID = id;
    newNode->customerName = name;
    newNode->left = NULL;
    newNode->right = NULL;
    newNode->height = 1;
    return newNode;
}

// Right rotation
Order* rightRotate(Order* y) {
    Order* x = y->left;
    Order* T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;

    return x;
}

// Left rotation
Order* leftRotate(Order* x) {
    Order* y = x->right;
    Order* T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;

    return y;
}

// Insert order into AVL Tree
Order* insertOrder(Order* node, int id, string name) {

    // Normal BST insertion
    if (node == NULL)
        return createOrder(id, name);

    if (id < node->orderID)
        node->left = insertOrder(node->left, id, name);
    else if (id > node->orderID)
        node->right = insertOrder(node->right, id, name);
    else
        return node; // Duplicate order ID not allowed

    // Update height
    node->height = 1 + max(height(node->left), height(node->right));

    // Get balance factor
    int balance = getBalance(node);

    // Left Left Case
    if (balance > 1 && id < node->left->orderID)
        return rightRotate(node);

    // Right Right Case
    if (balance < -1 && id > node->right->orderID)
        return leftRotate(node);

    // Left Right Case
    if (balance > 1 && id > node->left->orderID) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    // Right Left Case
    if (balance < -1 && id < node->right->orderID) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}

// In-order traversal (sorted order display)
void displayOrders(Order* root) {
    if (root != NULL) {
        displayOrders(root->left);
        cout << "Order ID: " << root->orderID
             << ", Customer: " << root->customerName << endl;
        displayOrders(root->right);
    }
}

// Main function
int main() {
    Order* root = NULL;

    root = insertOrder(root, 105, "Alice");
    root = insertOrder(root, 101, "Bob");
    root = insertOrder(root, 110, "Charlie");
    root = insertOrder(root, 102, "Diana");
    root = insertOrder(root, 108, "Evan");

    cout << "Orders in sorted order (by Order ID):\n";
    displayOrders(root);

    return 0;
}
