#include <iostream>
#include "CombatAbilities.h"
#include "CombatAbilities.mm"

using namespace std;

int main(){
    int allyHealth = 100;
    int enemyHealth = 500;

    cout << "Initialize battle . . ." << endl;
    
    ally mainCharacter;
    enemy firstBoss;
    gameCharacter haha;
    cout << endl;

/*
You'll see at the code below, that object "haha" under the base class gameCharacter could be substituted by
object "mainCharacter" under sub class ally
*/

    enemyHealth = enemyHealth - haha.Attack();
    cout << "Enemy health remaining " << allyHealth << " THIS USES THE BASE CLASS" << endl;
    cout << endl; 

    enemyHealth = enemyHealth - mainCharacter.Attack();
    cout << "Enemy health remaining " << allyHealth << " THIS USES THE SUB CLASS" << endl;
    cout << endl; 

//COMPARE BOTH EXAMPLES ABOVE, THEY USE 2 OBJECTS FROM BASE AND SUB CLASS BUT BOTH FUNCTION
    allyHealth = allyHealth - firstBoss.Attack();
    cout << "Ally health remaining " << allyHealth << endl;
    cout << endl;

    allyHealth = allyHealth + mainCharacter.Heal();
    cout << "Ally health remaining " << allyHealth << endl;
    cout << endl;

    allyHealth = allyHealth - firstBoss.Skill1();
    cout << "Ally health remaining " << allyHealth << endl;
    cout << endl;

    enemyHealth = enemyHealth - mainCharacter.Skill1();
    cout << "Enemy health remaining  " << enemyHealth << endl;
    cout << endl;

    allyHealth = allyHealth - firstBoss.Ultimate();
    cout << "Ally health remaining " << allyHealth << endl;
    cout << endl;

    enemyHealth = enemyHealth - mainCharacter.Skill1();
    cout << "Enemy health remaining  " << enemyHealth << endl;
    cout << endl;

    enemyHealth = enemyHealth - mainCharacter.Ultimate();
    cout << "Enemy health remaining  " << enemyHealth << endl;
    cout << endl;

    return 0;
}

