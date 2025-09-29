#include <iostream>
#include "CombatAbilities.h"
#include "CombatAbilities.mm"

using namespace std;
int allyHealth = 100;
int enemyHealth = 500;
ally mainCharacter;
enemy firstBoss;

int main()
{
    cout << "Initialize battle . . ." << endl;
    cout << endl;

    int allyTurn = 1;
    if (allyTurn = 1)
    { // ALLY TURN
        cout << "Turn start" << endl;
        showAbilities();
        int allyInput = getInput();
        abilitySelection(allyInput);
        displayEnemyHealth();
        allyTurn -= 1;
    }
    if (allyTurn = 0)
    { // ENEMY TURN
        int enemyInput = enemyCast();
        enemyAbilitySelection(enemyInput);
        displayAllyHealth();
        allyTurn++;

        return 0;
    }

    return 0;
}

// ALLY MENU
void showAbilities()
{
    cout << "1. Attack with weapon dealing ATK*WeaponMultiplier (Temporarily set 15-25)" << endl;
    //    cout << "2. Self-heal for certain amount" << endl;        SECTION REMOVED IN TESTING
    cout << "2. Summons 3* lightning strikes that each deal 25-40 damage" << endl;
    cout << "3. Gamble attack dealing damage between the range of 5-80" << endl;
    cout << "4. After reaching 10 energy, cast ultimate to deal guaranteed 150 damage" << endl;
    cout << endl;
}
char getInput()
{
    cout << " Enter action: " << endl;
    int input;
    cin >> input;
    return input;
}
char abilitySelection(int allyAbility)
{
    switch (allyAbility)
    {
    case 1:
        enemyHealth = enemyHealth - mainCharacter.allyAttack();
        cout << endl;
        break;
    case 2:
        enemyHealth = enemyHealth - mainCharacter.allySkill1();
        cout << endl;
        break;
    case 3:
        enemyHealth = enemyHealth - mainCharacter.allySkill2();
        cout << endl;
        break;
    case 4:
        enemyHealth = enemyHealth - mainCharacter.allyUltimate();
        cout << "Enemy health remaining  " << enemyHealth << endl;
        cout << endl;
        break;
    default:
        cout << "Invalid" << endl;
        break;
    }
    return 0;
}
int enemyCast()
{
    int min = 1;
    int max = 3;

    random_device rd;
    mt19937 eng(rd());
    uniform_int_distribution<> distr(min, max);

    int enemyCast = distr(eng);
    if (enemyCast <= 3)
    {
        cout << "PREAPRE YOURSELF" << endl;
    }
    return enemyCast;
}

// ENEMY LOGIC
char enemyAbilitySelection(int ability)
{
    switch (ability)
    {
    case 1:
        allyHealth = allyHealth - firstBoss.enemyAttack();
        break;
    case 2:
        allyHealth = allyHealth - firstBoss.enemySkill();
        break;
    case 3:
        allyHealth = allyHealth - firstBoss.enemyUltimate();
        break;
    default:
        cout << "Invalid" << endl;
        break;
    }
    return 0;
}
void displayEnemyHealth()
{
    cout << "Enemy health remaining  " << enemyHealth << endl;
    cout << endl;
}
void displayAllyHealth()
{
    cout << "Ally health remaining  " << allyHealth << endl;
    cout << endl;
}
