#include <iostream>
using namespace std;

bool mentor1 = true;
bool mentor2 = true;
bool mentor3 = true;

void WrapUp() {
    if (mentor1) { throw "Nothing on my side"; }
    if (mentor2) { throw "Mine too"; }
    if (mentor3) { throw "Okay guys that's a wrap"; }
}

void initiateWrapUp() {
    WrapUp();
}

int main() {
bool answer;
cout << "Okay mentors, anything to say?" << endl;
int input;
cin >> input;
if (input == 1)
{ answer = true;}
if (input == 0)
{ answer = false;}


if (answer == true)
{
cout << "Great job so far" << endl;
} if (answer == false){
    for (int i = 1; i < 4; i++) {
        try { initiateWrapUp(); }
        catch (const char* response) { cout << "Mentor " << i << ": " << response << endl; }
        
        // Update mentor status based on completion
        if (i == 1) { mentor1 = false; }
        if (i == 2) { mentor2 = false; }
        if (i == 3) { mentor3 = false; }
    }
}

    return 0;
}
