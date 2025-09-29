#include <iostream>
using namespace std;

int main(){
    bool bPassword = true;
    cout << "(1 for true; 0 for false) Magsasamgy ba tayo sa sabado?" << endl;
    bool bInput;
    cin >> bInput;

        if (bPassword == bInput){
        cout << "Oo talaga, wala kang choice" << endl;
        }   

         if (bPassword != bInput){
        cout << "Wala ka paring choice, magsasamgy tayo" << endl;
         }
        else {
                cout << "Sige ipilit mo" << endl;
         }


    
    double dPassword = 09.15;
    cout << "(MM.DD) Kelan ang anniv naten?" << endl;
    double dInput;
    cin >> dInput;

        if (dPassword == dInput) {
            cout << "Oke, pag di mo alam, salamat nalang sa lahat" << endl;
        }

        if (dPassword != dInput) {
            cout << "Salamat nalang sa lahat" << endl;
        }



    char cOptionA = 'a';
    char cOptionB = 'b';
    char cAnswer = 'c';
    char cOptionD = 'd';
    cout << "(Choose the letter of the correct answer) Ano ang piiiinnnnaaakkaaa (switis) paborito kong ulam?" << endl;
    cout << "a. Sisig" << endl;
    cout << "b. Bulanglang" << endl;
    cout << "c. Karekare" << endl;
    cout << "d. Monggo with maraming chicharon" << endl;
    char cInput;
    cin >> cInput;

        if (cInput == cOptionA) {
            cout << "Classic, pero minsan kasi depende sa nagluluto" << endl;
        }

        if (cInput == cOptionB) {
            cout << "Pwede pwede, laging nakakarami kanin pag bulanglang kaso medj rare" << endl;
        }

        if (cInput == cAnswer) {
            cout << "Awa ikwa me, dabest talaga Karekare, reminds me of Xmas" << endl;
        }

        if (cInput == cOptionD) {
            cout << "Underrated, lowkey would eat everyday" << endl;
        }
    

    return 0;
}