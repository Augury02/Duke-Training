#include <iostream>
#include "tropa.h"
#include "tropa.cpp"
using namespace std;

int main(){
    cout << "Starting program . . . " << endl;
    {
        Tropa swendel;
        cout << "Swendel: " << flush;
        swendel.makeTropa();
        swendel.speak();

        cout << endl;

        Tropa venz(swendel);
        cout << "Venz: " << flush;
        venz.makeStraight();
        venz.speak();

        Tropa jemuel = venz;
        cout << "Jemuel: " << flush;
        swendel.reply();

        return 0;
    }
}