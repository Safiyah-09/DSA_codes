#include <iostream>
using namespace std;

void selectionSort(int tokens[], int n) {
    for (int i = 0; i < n - 1; i++) {

        int minIndex = i; // assume current position has earliest token

        // find the earliest token in remaining list
        for (int j = i + 1; j < n; j++) {
            if (tokens[j] < tokens[minIndex]) {
                minIndex = j;
            }
        }

        // swap earliest token to correct position
        int temp = tokens[i];
        tokens[i] = tokens[minIndex];
        tokens[minIndex] = temp;
    }
}

int main() {
    int n;
    cout << "Enter number of appointment tokens: ";
    cin >> n;

    int tokens[n];
    cout << "Enter the tokens: ";
    for (int i = 0; i < n; i++) {
        cin >> tokens[i];
    }

    selectionSort(tokens, n);

    cout << "\nSorted appointment tokens (Earliest first): ";
    for (int i = 0; i < n; i++) {
        cout << tokens[i] << " ";
    }

    cout << endl;
    return 0;
}
