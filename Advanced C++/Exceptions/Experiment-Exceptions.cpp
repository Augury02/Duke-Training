#include <iostream>
using namespace std;

void WrapUp(){
    bool mentor1 = true;
    bool mentor2 = true;
    bool mentor3 = true;

    if(mentor1){ throw string("Nothing on my side");}
    if(mentor2){ throw "Mine too";}
    if(mentor3){ throw "Okay guys that's a wrap";}
}
void initiateWrapUp(){
    WrapUp();
}
int main(){
    try { initiateWrapUp();}
    catch(string &response){ cout << "Mentor1: " << response << endl;}
    catch(char const * response){ cout << "Mentor2: " << response << endl;}
    catch(char const * response){ cout << "Mentor3: " << response << endl;}
}
