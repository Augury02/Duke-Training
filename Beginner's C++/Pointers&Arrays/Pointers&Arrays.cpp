#include <iostream>
using namespace std;

int main() {
    const int NumOfCriminals = 6;
    string Criminal[NumOfCriminals] = {
        "Jemuel", "Ynah", "Keith", "Christian", "Venz", "Swendel"};

    string *pCrim = Criminal; 
    string *pEnd = Criminal + NumOfCriminals; 

    while (pCrim != pEnd) {
        cout << "Haha " << *pCrim << " kriminal" << endl;
        pCrim++;
    }
    return 0;
}
