#include <iostream>
#include <string>
using namespace std;

// Structure to store menu item details
struct MenuItem {
    string name;
    int price;
    string category;
    string ingredients;
};

// Lookup Table class
class MenuLookupTable {
public:
    MenuItem pizza;
    MenuItem burger;
    MenuItem pasta;
    MenuItem sandwich;

    MenuLookupTable();
    MenuItem search(string itemName);
    void display(MenuItem item);
    void updateItem();
};

// Constructor initializes menu items
MenuLookupTable::MenuLookupTable() {
    pizza = {"Pizza", 250, "Main Course", "Cheese, Tomato"};
    burger = {"Burger", 150, "Fast Food", "Bun, Patty, Cheese"};
    pasta = {"Pasta", 200, "Main Course", "Cream, Sauce"};
    sandwich = {"Sandwich", 120, "Snacks", "Bread, Veggies"};
}

// Direct lookup (O(1))
MenuItem MenuLookupTable::search(string itemName) {
    if (itemName == pizza.name)
        return pizza;
    if (itemName == burger.name)
        return burger;
    if (itemName == pasta.name)
        return pasta;
    if (itemName == sandwich.name)
        return sandwich;

    return {"", 0, "", ""};
}

// Display menu item details
void MenuLookupTable::display(MenuItem item) {
    if (item.name != "") {
        cout << "\nDish Name: " << item.name << endl;
        cout << "Price: ₹" << item.price << endl;
        cout << "Category: " << item.category << endl;
        cout << "Ingredients: " << item.ingredients << endl;
    } else {
        cout << "Menu item not found.\n";
    }
}

// Update menu item details
void MenuLookupTable::updateItem() {
    string name;
    cout << "Enter dish name to update: ";
    cin.ignore();
    getline(cin, name);

    if (name == pizza.name || name == burger.name ||
        name == pasta.name || name == sandwich.name) {

        int price;
        string category, ingredients;

        cout << "Enter new price: ";
        cin >> price;
        cin.ignore();
        cout << "Enter category: ";
        getline(cin, category);
        cout << "Enter ingredients: ";
        getline(cin, ingredients);

        if (name == pizza.name)
            pizza = {name, price, category, ingredients};
        else if (name == burger.name)
            burger = {name, price, category, ingredients};
        else if (name == pasta.name)
            pasta = {name, price, category, ingredients};
        else
            sandwich = {name, price, category, ingredients};

        cout << "Menu updated successfully.\n";
    } else {
        cout << "Dish not found in menu.\n";
    }
}

// Main function
int main() {
    MenuLookupTable menu;
    int choice;
    string dishName;

    while (true) {
        cout << "\nMenu Lookup System\n";
        cout << "1. Search Dish\n";
        cout << "2. Update Dish\n";
        cout << "3. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            cin.ignore();
            cout << "Enter dish name: ";
            getline(cin, dishName);
            menu.display(menu.search(dishName));
            break;

        case 2:
            menu.updateItem();
            break;

        case 3:
            cout << "Exiting system...\n";
            return 0;

        default:
            cout << "Invalid choice.\n";
        }
    }
}
