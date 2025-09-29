#ifndef COMBATABILITIES_H_
#define COMBATABILITIES_H_

class gameCharacter {
public:
    void endTurn(); 
};

class ally: public gameCharacter {
    public:
        int allyAttack();       //Attack with weapon dealing ATK*WeaponMultiplier (Temporarily set 15-25); 0 cooldown, generate 2 energy
        int allyHeal();         //Self-heal for certain amount; cooldown 3 turns, generate 1 energy
        int allySkill1();       //Summons 3* lightning strikes that each deal 25-40 damage; cooldown 2 turns, generate 0 energy
        int allySkill2();       //Gamble attack dealing damage between the range of 5-80; cooldown 1 turn, generate 1 energy
        int allyUltimate();     //After reaching 10 energy, cast ultimate to deal guaranteed 150 damage
        ally();
};

class enemy: public gameCharacter {
    public:
        int enemyAttack();      //Attack dealing 10-15 damage
        int enemySkill();       //Attack dealing 15-30 damage; cooldown 2 turns
        int enemyUltimate();     //After reaching 10 energy, cast ultimate to deal guaranteed 50 damage
        enemy();
};

void showAbilities();               //cout display
char getInput();                    //user input
char abilitySelection();            //switch option
int enemyCast();                   //randomizer
char enemyAbilitySelection();       //Switch option





#endif