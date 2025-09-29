#include <iostream>
#include <string>

using namespace std;

template<class T>
void reply(T n) {
    cout << n << " ((Reply as a Template function))" << endl;
}

void speak(string content) {
    cout << content << " ((Speak as a Non-template function))" << endl;
}

void response(int value) {          //IMPLEMENTATION OF FUNCTION POINTER
    for (int i = 1; i <= 4; i++) {
        if (i == 1) {
            cout << "Kent: Jem nooooo (" << value << ")" << endl;
        }
        if (i == 2) {
            cout << "Keith: HAHAHAHHAHA (" << value << ")" << endl;
        }
        if (i == 3) {
            cout << "Christian: *Redacted* (" << value << ")" << endl;
        }
        if (i == 4) {
            cout << "Ynah: haha (" << value << ")" << endl;
        }
        value++;
    }
}

int main() {
    cout << "////////////////////" << endl;
    cout << "I can take on " << endl;
    reply<int>(5); // Using template function with int argument
    cout << "men . . ." << endl;

    cout << endl;
    cout << endl;
    speak("Venz: In a fight right?"); // Using non-template version
    reply<string>("Jem: *Insert iconic anakin smirk*"); // Using template function with string argument
    speak("Venz: . . . in a fight, right?"); // Using non-template version

    response(1);        //IMPLEMENTATION OF FUNCTION POINTER

    return 0;
}
