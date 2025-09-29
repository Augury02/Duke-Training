#ifndef COMBATABILITIES_H_
#define COMBATABILITIES_H_

class gameCharacter {
public:
    int Attack();
    int Heal();
    int Skill1();
    int Skill2();
    int Ultimate();
    gameCharacter();
};

class ally: public gameCharacter {          //APPLICATION OF SINGLE RESPONSIBILITY PRINCIPLE
    public:
        int Attack();       //Attack with weapon dealing ATK*WeaponMultiplier (Temporarily set 15-25); 0 cooldown, generate 2 energy
        int Heal();         //Self-heal for certain amount; cooldown 3 turns, generate 1 energy
        int Skill1();       //Summons 3* lightning strikes that each deal 25-40 damage; cooldown 2 turns, generate 0 energy
        int Skill2();       //Gamble attack dealing damage between the range of 5-80; cooldown 1 turn, generate 1 energy
        int Ultimate();     //After reaching 10 energy, cast ultimate to deal guaranteed 150 damage
        ally();
};

class enemy: public gameCharacter {         //APPLICATION OF SINGLE RESPONSIBILITY PRINCIPLE
    public:
        int Attack();      //Attack dealing 10-15 damage
        int Skill1();       //Attack dealing 15-30 damage; cooldown 2 turns
        int Ultimate();     //After reaching 10 energy, cast ultimate to deal guaranteed 50 damage
        enemy();
};

void showAbilities();               //cout display
char getInput();                    //user input
char abilitySelection();            //switch option
int enemyCast();                   //randomizer
char enemyAbilitySelection();       //Switch option





#endif