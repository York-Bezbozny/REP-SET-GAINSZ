#include <iostream>
#include <string>
#include <limits> // For input validation
#include "characters.h" // Include the header file

using namespace std;

// Function prototypes (Only those used in main.cpp)
void intro();
void menu();

int main() {
    srand(time(0)); 
    intro();
    menu();
    return 0;
}

void intro() {
    cout << "Welcome to the REP-SET program, soldier! You are a young recruit in the Federated Isometocracy of Terra, and you have the potential to become a powerful pilot of a REP-SET mech.\n";
    cout << "But first, you must complete your basic training. In this program, you will push your body and mind to the limit, learning the skills you need to survive and fight on the battlefield.\n";
    cout << "Are you ready to begin?\n";
}

void menu() {
    int choice;
    do {
        cout << "\nMain Menu\n";
        cout << "1. Create Character\n";
        cout << "2. Remove Character\n";
        cout << "3. Print Characters\n";
        cout << "4. Find Character\n";
        cout << "5. Quit\n";
        cout << "Enter your choice: ";

        if (!(cin >> choice)) {
            cout << "Invalid choice. Please enter a number.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        switch (choice) {
            case 1: createCharacter(); break;
            case 2: removeCharacter(); break;
            case 3: printCharacters(); break;
            case 4: findCharacter(); break;
            case 5: cout << "Farewell, soldier!\n"; break;
            default: cout << "Invalid choice.\n";
        }
    } while (choice != 5);
}
