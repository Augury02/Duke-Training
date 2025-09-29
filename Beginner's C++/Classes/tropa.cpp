#include <iostream>
#include "tropa.h"
using namespace std;

Tropa::Tropa(){
    cout << "Jemuel: I can take on 5 men ..." << endl;
}
Tropa::~Tropa(){
    for (int i=0; i<=4; i++) {
        if (i=1){ 
            cout << "Kent: Jem nooooo" << endl;
        }
        if (i=2) {
            cout << "Keith: HAHAHAHHAHA" << endl;
        }
        if (i=3) {
            cout << "Christian: *Redacted*" << endl;
        }
        if (i=4) {
            cout << "Ynah: haha" << endl;
        }
    }
}
void Tropa::reply() {
    cout << "haha. . . ha.. :DD" << endl;
}
void Tropa::speak() {

    if (TropaKaBa){
        cout << "in league?" << endl;
    } else {
        cout << "in a fight... right?" << endl;
    }
}
void Tropa::makeTropa(){
    TropaKaBa=true;
}
void Tropa::makeStraight(){
    TropaKaBa=false;
}