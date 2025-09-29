#include <iostream>
using namespace std;

// Header / Function Prototype
void initializeBirthday();
int showMenu();
void processSelection(int);


// Main
int main() {
    initializeBirthday();
    int selection;
    do {
        selection = showMenu();
        processSelection(selection);
    } while (selection != 4);

    return 0;
}

// Source code
void initializeBirthday(){
    string password = "birthday";
    cout << "Anong meron ngayon? (Answer in lowercase)" << endl;
    string input;
    cin >> input;

    while (input != password) {
        cout << "Password incorrect, try again." << endl;
        cin >> input;
    }
    cout << "Initializing birthday present . . ." << endl;
}

int showMenu(){
    cout << "Select menu option (1-4):" << endl;
    cout << "1. Message" << endl;
    cout << "2. Poem" << endl;
    cout << "3. Teaser" << endl;
    cout << "4. Exit" << endl;
    cout << "Input your selection: " << flush;
    int menuInput;
    cin >> menuInput;
    return menuInput;
}

void processSelection(int option){
    switch (option) {
    case 1:
        cout << "Insert Message" << endl;

        cout << "=========================================================================" << endl;
        break;
    case 2:
        cout << "Insert Poem" << endl;
        cout << "=========================================================================" << endl;


        break;
    case 3:
        cout << "Teaser" << endl;
        cout << "=========================================================================" << endl;

        break;
    case 4:
        cout << "Happy birthday!!" << endl;
        cout << "Closing present . . .   " << endl;
        cout << "=========================================================================" << endl;
        break;
    default:
        cout << "Entry not recognized, try again." << endl;
        cout << "=========================================================================" << endl;
        break;
    }
}
