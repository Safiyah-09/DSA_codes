#include <iostream>
using namespace std;

// Trie Node structure
struct TrieNode {
    TrieNode* children[26];
    bool isEnd;   // Marks complete customer name or dish

    TrieNode() {
        isEnd = false;
        for (int i = 0; i < 26; i++)
            children[i] = NULL;
    }
};

// Insert customer name or dish into Trie
void insertPreference(TrieNode* root, string word) {
    TrieNode* current = root;

    for (char c : word) {
        int index = c - 'a';
        if (current->children[index] == NULL)
            current->children[index] = new TrieNode();
        current = current->children[index];
    }
    current->isEnd = true;
}

// Search exact customer name or dish
bool searchPreference(TrieNode* root, string word) {
    TrieNode* current = root;

    for (char c : word) {
        int index = c - 'a';
        if (current->children[index] == NULL)
            return false;
        current = current->children[index];
    }
    return current->isEnd;
}

// Display auto-suggestions for a prefix
void displaySuggestions(TrieNode* root, string prefix) {
    if (root->isEnd)
        cout << prefix << endl;

    for (int i = 0; i < 26; i++) {
        if (root->children[i] != NULL) {
            char nextChar = 'a' + i;
            displaySuggestions(root->children[i], prefix + nextChar);
        }
    }
}

// Prefix search for customer history / dishes
void prefixSearch(TrieNode* root, string prefix) {
    TrieNode* current = root;

    for (char c : prefix) {
        int index = c - 'a';
        if (current->children[index] == NULL) {
            cout << "No records found for this prefix.\n";
            return;
        }
        current = current->children[index];
    }

    cout << "Suggestions based on prefix \"" << prefix << "\":\n";
    displaySuggestions(current, prefix);
}

// Main function
int main() {
    TrieNode* root = new TrieNode();
    int choice;
    string input;

    while (true) {
        cout << "\nMenu:\n";
        cout << "1. Add Customer Name / Dish\n";
        cout << "2. Search Exact Customer/Dish\n";
        cout << "3. Prefix Search (Auto-Suggestions)\n";
        cout << "4. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        if (choice == 1) {
            cout << "Enter customer name or dish (lowercase): ";
            cin >> input;
            insertPreference(root, input);
            cout << "Stored successfully.\n";
        }
        else if (choice == 2) {
            cout << "Enter name or dish to search: ";
            cin >> input;
            if (searchPreference(root, input))
                cout << "Record found.\n";
            else
                cout << "Record not found.\n";
        }
        else if (choice == 3) {
            cout << "Enter prefix: ";
            cin >> input;
            prefixSearch(root, input);
        }
        else if (choice == 4) {
            cout << "Exiting system.\n";
            break;
        }
        else {
            cout << "Invalid choice.\n";
        }
    }

    return 0;
}
