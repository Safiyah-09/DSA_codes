#include <iostream>
#include <string>
using namespace std;

#define CHAR_SIZE 256   // Total ASCII characters

// Create Bad Character Table
void badCharTable(string pattern, int badChar[]) {
    int m = pattern.length();

    // Initialize all occurrences as -1
    for (int i = 0; i < CHAR_SIZE; i++)
        badChar[i] = -1;

    // Fill actual position of characters in pattern
    for (int i = 0; i < m; i++)
        badChar[(int)pattern[i]] = i;
}

// Boyer–Moore Search Function
bool boyerMooreSearch(string text, string pattern) {
    int m = pattern.length();
    int n = text.length();
    int badChar[CHAR_SIZE];

    badCharTable(pattern, badChar);

    int shift = 0;

    while (shift <= (n - m)) {
        int j = m - 1;

        // Compare from right to left
        while (j >= 0 && pattern[j] == text[shift + j])
            j--;

        // If pattern matches
        if (j < 0) {
            return true;
        }
        else {
            // Shift pattern using bad character rule
            shift += max(1, j - badChar[text[shift + j]]);
        }
    }
    return false;
}

int main() {
    string menuDescriptions[] = {
        "Cheese pizza with tomato and basil",
        "Spicy chicken burger with sauce",
        "Creamy pasta with mushrooms",
        "Grilled sandwich with vegetables"
    };

    int menuSize = 4;
    string keyword;

    cout << "Enter ingredient or keyword to search: ";
    getline(cin, keyword);

    cout << "\nDishes containing \"" << keyword << "\":\n";

    bool found = false;
    for (int i = 0; i < menuSize; i++) {
        if (boyerMooreSearch(menuDescriptions[i], keyword)) {
            cout << "- " << menuDescriptions[i] << endl;
            found = true;
        }
    }

    if (!found)
        cout << "No matching dishes found.\n";

    return 0;
}
