#include <iostream>
using namespace std;

enum Color { RED, BLACK };

// Node structure for insurance record
struct Node {
    int policyNumber;
    Color color;
    Node *left, *right, *parent;

    Node(int policy) {
        policyNumber = policy;
        color = RED;
        left = right = parent = nullptr;
    }
};

// Red-Black Tree class
class RedBlackTree {
public:
    Node *root;

    RedBlackTree() {
        root = nullptr;
    }

    // Perform left rotation
    void rotateLeft(Node* &root, Node* &pt) {
        Node *rightChild = pt->right;
        pt->right = rightChild->left;

        if (pt->right != nullptr)
            pt->right->parent = pt;

        rightChild->parent = pt->parent;

        if (pt->parent == nullptr)
            root = rightChild;

        else if (pt == pt->parent->left)
            pt->parent->left = rightChild;

        else
            pt->parent->right = rightChild;

        rightChild->left = pt;
        pt->parent = rightChild;
    }

    // Perform right rotation
    void rotateRight(Node* &root, Node* &pt) {
        Node *leftChild = pt->left;
        pt->left = leftChild->right;

        if (pt->left != nullptr)
            pt->left->parent = pt;

        leftChild->parent = pt->parent;

        if (pt->parent == nullptr)
            root = leftChild;

        else if (pt == pt->parent->left)
            pt->parent->left = leftChild;

        else
            pt->parent->right = leftChild;

        leftChild->right = pt;
        pt->parent = leftChild;
    }

    // Fix violations after insertion
    void fixViolation(Node* &root, Node* &pt) {
        Node *parentPt = nullptr;
        Node *grandParentPt = nullptr;

        while ((pt != root) && (pt->color != BLACK) &&
               (pt->parent->color == RED)) {

            parentPt = pt->parent;
            grandParentPt = pt->parent->parent;

            // Case A: Parent is left child of grandparent
            if (parentPt == grandParentPt->left) {
                Node *unclePt = grandParentPt->right;

                // Case 1: Uncle is RED
                if (unclePt != nullptr && unclePt->color == RED) {
                    grandParentPt->color = RED;
                    parentPt->color = BLACK;
                    unclePt->color = BLACK;
                    pt = grandParentPt;
                }

                // Case 2: pt is right child
                else {
                    if (pt == parentPt->right) {
                        rotateLeft(root, parentPt);
                        pt = parentPt;
                        parentPt = pt->parent;
                    }

                    // Case 3: pt is left child
                    rotateRight(root, grandParentPt);
                    swap(parentPt->color, grandParentPt->color);
                    pt = parentPt;
                }
            }

            // Case B: Parent is right child of grandparent
            else {
                Node *unclePt = grandParentPt->left;

                if (unclePt != nullptr && unclePt->color == RED) {
                    grandParentPt->color = RED;
                    parentPt->color = BLACK;
                    unclePt->color = BLACK;
                    pt = grandParentPt;
                }
                else {
                    if (pt == parentPt->left) {
                        rotateRight(root, parentPt);
                        pt = parentPt;
                        parentPt = pt->parent;
                    }

                    rotateLeft(root, grandParentPt);
                    swap(parentPt->color, grandParentPt->color);
                    pt = parentPt;
                }
            }
        }

        root->color = BLACK;
    }

    // Insert insurance policy number
    void insert(int policyNumber) {
        Node *pt = new Node(policyNumber);

        Node *parent = nullptr;
        Node *current = root;

        // Normal BST insert
        while (current != nullptr) {
            parent = current;

            if (pt->policyNumber < current->policyNumber)
                current = current->left;
            else
                current = current->right;
        }

        pt->parent = parent;

        if (parent == nullptr)
            root = pt;
        else if (pt->policyNumber < parent->policyNumber)
            parent->left = pt;
        else
            parent->right = pt;

        // Fix RBT violation
        fixViolation(root, pt);
    }

    // Search for an insurance policy
    bool search(int policyNumber) {
        Node *current = root;

        while (current != nullptr) {
            if (policyNumber == current->policyNumber)
                return true;

            else if (policyNumber < current->policyNumber)
                current = current->left;

            else
                current = current->right;
        }
        return false;
    }
};

int main() {
    RedBlackTree rbt;
    int choice, policy;

    while (true) {
        cout << "\n--- Insurance Verification (RBT) ---\n";
        cout << "1. Insert Policy\n2. Search Policy\n3. Exit\nEnter choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter policy number to insert: ";
                cin >> policy;
                rbt.insert(policy);
                cout << "Policy inserted & balanced.\n";
                break;

            case 2:
                cout << "Enter policy number to search: ";
                cin >> policy;
                if (rbt.search(policy))
                    cout << "Policy FOUND in system.\n";
                else
                    cout << "Policy NOT found!\n";
                break;

            case 3:
                return 0;

            default:
                cout << "Invalid choice.\n";
        }
    }
}
