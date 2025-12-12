#include <iostream>
#include <vector>
#include <string>
using namespace std;

// Function to build LPS (Longest Prefix Suffix) array
void buildLPS(string pattern, vector<int>& lps) {
    int len = 0;
    lps[0] = 0;

    int i = 1;
    while (i < pattern.length()) {
        if (pattern[i] == pattern[len]) {
            len++;
            lps[i] = len;
            i++;
        } else {
            if (len != 0) {
                len = lps[len - 1];
            } else {
                lps[i] = 0;
                i++;
            }
        }
    }
}

// KMP Search function
void KMPSearch(string text, string pattern) {
    int n = text.length();
    int m = pattern.length();

    vector<int> lps(m);
    buildLPS(pattern, lps);

    int i = 0; // text index
    int j = 0; // pattern index

    bool found = false;

    while (i < n) {
        if (pattern[j] == text[i]) {
            i++;
            j++;
        }

        if (j == m) {
            cout << "Symptom found at position: " << (i - j) << endl;
            found = true;
            j = lps[j - 1];
        }
        else if (i < n && pattern[j] != text[i]) {
            if (j != 0)
                j = lps[j - 1];
            else
                i++;
        }
    }

    if (!found)
        cout << "Symptom NOT found in notes." << endl;
}

int main() {
    string notes, symptom;

    cout << "Enter patient notes:\n";
    getline(cin, notes);

    cout << "Enter symptom to search: ";
    getline(cin, symptom);

    cout << "\nSearching for symptom...\n";
    KMPSearch(notes, symptom);

    return 0;
}
