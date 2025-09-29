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
    cout << endl;

    enemyHealth = enemyHealth - mainCharacter.allyAttack();
    cout << "Enemy health remaining  " << enemyHealth << endl;
    cout << endl;

    allyHealth = allyHealth - firstBoss.enemyAttack();
    cout << "Ally health remaining " << allyHealth << endl;
    cout << endl;

    allyHealth = allyHealth + mainCharacter.allyHeal();
    cout << "Ally health remaining " << allyHealth << endl;
    cout << endl;

    enemyHealth = enemyHealth - mainCharacter.allySkill1();
    cout << "Enemy health remaining  " << enemyHealth << endl;
    cout << endl;

    enemyHealth = enemyHealth - mainCharacter.allySkill2();
    cout << "Enemy health remaining  " << enemyHealth << endl;
    cout << endl;

    enemyHealth = enemyHealth - mainCharacter.allyUltimate();
    cout << "Enemy health remaining  " << enemyHealth << endl;
    cout << endl;

    return 0;
}

