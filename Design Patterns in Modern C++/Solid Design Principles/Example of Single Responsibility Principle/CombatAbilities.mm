#include <iostream>
#include <random>
#include "CombatAbilities.h"
using namespace std;

//Constructors
ally::ally(){
    cout << "Champion selected" << endl;
}
enemy::enemy(){
    cout << "Enemy has been summoned" << endl;
    cout << "Prepare for combat" << endl;
}

//AllySkillSet
int ally::allyAttack(){       
        int min = 15;
        int max = 25;

        random_device rd;   // Obtain a random number from hardware
        mt19937 eng(rd());  // Seed the generator
        uniform_int_distribution<> distr(min, max);     // Define the range

        int basicAttackDamage = distr(eng);     // Generate the random number
        if (basicAttackDamage >= 22){cout << "CRITICAL HIT" << endl;};
        if (basicAttackDamage <= 18){cout << "POOR HIT" << endl;}
        cout << "You've dealt " << basicAttackDamage << " using Basic Attack" << endl;          //USE THIS FOR COMPARISON
        return basicAttackDamage;
        }
int ally::allyHeal(){          
        int healAmount = 25;
        cout << "You've healed " << healAmount << " health" << endl;
        return healAmount;
    }
int ally::allySkill1(){ 
        int damageSum = 0;

        // 1st instance of damage
        int min1 = 25; 
        int max1 = 40;
        random_device rd1; 
        mt19937 eng1(rd1()); 
        uniform_int_distribution<> distr1(min1, max1); 
        int allySkill1Damage1 = distr1(eng1); 
        damageSum += allySkill1Damage1;

        //2nd instance of damage
        random_device rd2; 
        mt19937 eng2(rd2()); 
        uniform_int_distribution<> distr2(min1, max1); 

        int allySkill1Damage2 = distr2(eng2); 
        damageSum += allySkill1Damage2;

        // 3rd instance of damage
        random_device rd3; 
        mt19937 eng3(rd3()); 
        uniform_int_distribution<> distr3(min1, max1); 

        int allySkill1Damage3 = distr3(eng3); 
        damageSum += allySkill1Damage3;
        if (damageSum >= 110){cout << "CRITICAL HIT" << endl;};
        if (damageSum <= 80){cout << "POOR HIT" << endl;}
        cout << "You've dealt " << damageSum << " damage using Lightning strike" << endl;
        return damageSum;
    }
int ally::allySkill2(){  
        int min = 5;
        int max = 80;

        random_device rd;   // Obtain a random number from hardware
        mt19937 eng(rd());  // Seed the generator
        uniform_int_distribution<> distr(min, max);     // Define the range

        int skill3Damage = distr(eng);     // Generate the random number
        if (skill3Damage >= 75){cout << "CRITICAL HIT" << endl;};
        if (skill3Damage <= 15){cout << "MISSED THE GAMBA" << endl;}
        cout << "You've dealt " << skill3Damage << " damage using Gamble Draw" << endl;
        return skill3Damage;
}       
int ally::allyUltimate(){
        int ultiDamage = 150;
        cout << "You've dealt " << ultiDamage << " damage using Ultimate" << endl;
        return ultiDamage;
}


//EnemySKillSet
int enemy::enemyAttack(){      
        int min = 10;
        int max = 15;
        random_device rd; 
        mt19937 eng(rd()); 
        uniform_int_distribution<> distr(min, max); 

        int basicAttackDamage = distr(eng); 
        cout << "The enemy used 'NOTHING ON MY SIDE' dealing " << basicAttackDamage << " damage" << endl;
        return basicAttackDamage;
        }
int enemy::enemySkill(){      
        int min = 15;
        int max = 30;
        random_device rd; 
        mt19937 eng(rd()); 
        uniform_int_distribution<> distr(min, max); 

        int enemySkillDamage = distr(eng); 
        cout << "The enemy used 'MINE TOO' dealing " << enemySkillDamage << " damage" << endl;
        return enemySkillDamage;
        }        
int enemy::enemyUltimate(){      
        int min = 10;
        int max = 15;
        random_device rd; 
        mt19937 eng(rd()); 
        uniform_int_distribution<> distr(min, max); 

        int enemyUltimateDamage = distr(eng); 
        cout << "The enemy used 'OKAY GUYS, THAT'S A WRAP' " << enemyUltimateDamage << " damage" << endl;
        return enemyUltimateDamage;
        }
