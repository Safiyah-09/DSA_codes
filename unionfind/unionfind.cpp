#include <iostream>
using namespace std;

// Find operation: checks if two doctors belong to the same department
int findDept(int parent[], int d1, int d2)
{
    if (parent[d1] == parent[d2])
        return 1;   // conflict (same department)
    else
        return 0;   // no conflict
}

// Union operation: assigns a doctor to a department (group)
void unionDept(int parent[], int n, int d1, int d2)
{
    int temp = parent[d1];

    // Merge both doctors into one department (set)
    for (int i = 0; i < n; i++)
    {
        if (parent[i] == temp)
            parent[i] = parent[d2];
    }
}

int main()
{
    int n;
    cout << "Enter number of doctors: ";
    cin >> n;

    int parent[n];

    // Initially each doctor is in their own separate department
    for (int i = 0; i < n; i++)
    {
        parent[i] = i;
    }

    int choice, d1, d2;

    do {
        cout << "\n1. Assign Doctor to Department (Union)";
        cout << "\n2. Check Scheduling Conflict (Find)";
        cout << "\n3. Exit\nEnter choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            cout << "Enter two doctors to assign under same department: ";
            cin >> d1 >> d2;
            unionDept(parent, n, d1, d2);
            cout << "Doctors assigned under same department.\n";
            break;

        case 2:
            cout << "Enter two doctors to check scheduling conflict: ";
            cin >> d1 >> d2;

            if (findDept(parent, d1, d2))
                cout << "Conflict detected! Both doctors belong to the same department.\n";
            else
                cout << "No conflict. Doctors are in different departments.\n";
            break;

        case 3:
            cout << "Exiting...\n";
            break;

        default:
            cout << "Invalid choice!\n";
        }

    } while (choice != 3);

    return 0;
}
