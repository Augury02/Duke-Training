#include <iostream>
using namespace std;

int main() {
    string password = "Jayvelyn";
    cout << "Enter password: " << flush;
    string userInput;
    cin >> userInput;

    if (userInput == password){
        cout << "Password accepted, proceed" << endl;
    }

    if (userInput != password) {
        cout << "Password incorrect, retry" << endl;
    }

    return 0;
}