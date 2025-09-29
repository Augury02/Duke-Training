#include <iostream>
#include <string>

using namespace std;

int main() {
    string appear1 = "The quick";
    string appear2 = "brown fox";
    string notAppear1 = "THIS STRING SHOULD NOT APPEAR";
    string appear3 = "jumped over";
    string appear4 = "the lazy dog";
    string notAppear2 = "THIS STRING SHOULD ALSO NOT APPEAR";
    double birthday{09.15};     //alternative way of defining variables

    cout << " " << endl;
    cout << " " << endl;
    //LAMBDA CAPTURE EXPRESSIONS
    // Capture only selected values by value
    [appear1, appear2, appear3, appear4]() {
        cout << "Capture only selected values" << endl;
        cout << appear1 << " " << appear2 << " " << appear3 << " " << appear4 << endl;
        cout << " " << endl;
    }();

    // Capture all local variables, with some via reference
    [=, &notAppear1, &notAppear2]() {
        notAppear1 = "Szechuan sauce";
        notAppear2 = "Worcestershire sauce";

        cout << "Capture all local variables, with some via reference" << endl;
        cout << appear1 << " " << appear2 << " " << appear3 << " " << appear4 << endl;
        cout << notAppear1 << " and " << notAppear2;
        cout << " " << endl;
        cout << " " << endl;
    }();

    [birthday]() mutable {
        birthday = 12.06;
        cout << " " << endl;
        cout << "Mutable Lambda " << endl;
        cout << "Your birthday is on " << birthday << endl;
        cout << " " << endl;
    }();

    // LAMBDA RETURN VALUES AND PARAMETERS
    auto life = [](double a, double b) -> double {
        cout << "Lambda return values and parameters" << endl;
        
        if (a + b != 42.0) {
            cout << "You need to keep searching" << endl;
            return 0;
        }
        if (a + b == 42.0){
            cout << "You found the meaning of life" << endl;
            return a + b;
        }
    };

    cout << life(15.0, 27.0) << endl;
    cout << life(5.0, 2.7) << endl;

    return 0;
}


/*
OTHER NOTES
Covered topics: Elision; Constructors and Memory (mostly additional theoretical stuff on already existing features)
R Values: Temporary unnamed object w/ no persistent memory loc
L Values: Object that occupies identifiable location
Move consturctor: takes rvalue reference as its parameter
Move assignment: invoked when assigning rvalue to an object w/ same type; mostly used for resource transfer\
Static Cast: Used for explicit type conversion between related types
Dynamic Cast: Used for performing downcasting and checking polymorphic class hierarchies

*/