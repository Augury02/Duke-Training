#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <random>

using namespace std;

// Function prototype for enemyCast
int enemyCast();

//Combat Encounter Simulation
bool battle() {
    int playerHealth = 100;
    int monsterHealth = 500;
    int playerAttack, monsterAttack;
    int playerInput;

    cout << endl;
    cout << "A wild monster appears!" << endl;


    while (playerHealth > 0 && monsterHealth > 0) {
        //Interface of Player Turn
        cout << "Your turn - Choose your action (1-3):" << endl;
        cout << "1. Attack with weapon dealing 15-25 damage" << endl;
        cout << "2. Summons 3* lightning strikes that each deal 25-40 damage" << endl;
        cout << "3. Gamble attack dealing damage between the range of 5-80" << endl;
        cout << endl;
        cin >> playerInput;

        if(playerInput == 1){
            int min = 15;
            int max = 25;

            random_device rd;   //obtain a random number from hardware
            mt19937 eng(rd());  //seed the generator
            uniform_int_distribution<> distr(min, max);     //define the range

            int basicAttackDamage = distr(eng);     //generate the random number
            if (basicAttackDamage >= 22){cout << "CRITICAL HIT" << endl;}
            if (basicAttackDamage <= 18){cout << "POOR HIT" << endl;}
            cout << "You've dealt " << basicAttackDamage << " using Basic Attack" << endl;
            monsterHealth -= basicAttackDamage;
            cout << "Enemy Health remaining: " << monsterHealth << endl;
            cout << endl;
        }
        
        else if (playerInput == 2){
            int damageSum = 0;

            for(int i = 0; i < 3; ++i){
                int min = 25; 
                int max = 40;
                random_device rd; 
                mt19937 eng(rd()); 
                uniform_int_distribution<> distr(min, max); 
                int lightningDamage = distr(eng); 
                damageSum += lightningDamage;
            }
            if (damageSum >= 110){cout << "CRITICAL HIT" << endl;}
            if (damageSum <= 80){cout << "POOR HIT" << endl;}
            cout << "You've dealt " << damageSum << " damage using Lightning strike" << endl;
            monsterHealth -= damageSum;
            cout << "Enemy Health remaining: " << monsterHealth << endl;
            cout << endl;
        }

        else if (playerInput == 3) {
            int min = 5;
            int max = 80;

            random_device rd;   //random number from hardware
            mt19937 eng(rd());  //seed the generator
            uniform_int_distribution<> distr(min, max);     //define the range

            int gambleDamage = distr(eng);     //generate the random number
            if (gambleDamage >= 75){cout << "CRITICAL HIT" << endl;}
            if (gambleDamage <= 15){cout << "MISSED THE GAMBLE" << endl;}
            cout << "You've dealt " << gambleDamage << " damage using Gamble Draw" << endl;
            monsterHealth -= gambleDamage;
            cout << "Enemy Health remaining: " << monsterHealth << endl;
            cout << endl;
        }
        
        // Check if monster is defeated
        if (monsterHealth <= 0) {
            cout << "You defeated the monster!" << endl;
            return true;
        }

        // Monster's turn
        int monsterAction = enemyCast();
        int monsterAttack;
        
        if (monsterAction == 1){
            int min1 = 10;
            int max1 = 15;
            random_device rd; 
            mt19937 eng(rd()); 
            uniform_int_distribution<> distr(min1, max1); 

            monsterAttack = distr(eng); 
            cout << "The enemy used 'NOTHING ON MY SIDE' dealing " << monsterAttack << " damage" << endl;
            playerHealth -= monsterAttack;
        } 
        else if (monsterAction == 2){
            int min2 = 15;
            int max2 = 30;
            random_device rd; 
            mt19937 eng(rd()); 
            uniform_int_distribution<> distr(min2, max2); 

            monsterAttack = distr(eng); 
            cout << "The enemy used 'MINE TOO' dealing " << monsterAttack << " damage" << endl;
            playerHealth -= monsterAttack;
        } 
        else if (monsterAction == 3){
            int min3 = 10;
            int max3 = 15;
            random_device rd; 
            mt19937 eng(rd()); 
            uniform_int_distribution<> distr(min3, max3); 

            monsterAttack = distr(eng); 
            cout << "The enemy used 'OKAY GUYS, THAT'S A WRAP' dealing " << monsterAttack << " damage" << endl;
            playerHealth -= monsterAttack;
        }

        cout << endl;
        cout << "Monster attacks! You received " << monsterAttack << " damage." << endl;
        cout << "Player Health remaining: " << playerHealth << endl;
        cout << endl;

        // Check if player is defeated
        if (playerHealth <= 0) {
            cout << "You were defeated by the monster!" << endl;
            return false;
        }
    }
    return false;
}

// Function to determine the action of the enemy
int enemyCast(){
    int min = 1;
    int max = 3;

    random_device rd;
    mt19937 eng(rd());
    uniform_int_distribution<> distr(min, max);

    int rand = distr(eng);
    if (rand == 1)
    {cout << "PREPARE YOURSELF" << endl;}
    return rand;
}

int main() {
    srand(time(0));

    cout << "Welcome to the Primitive Game!" << endl;
    cout << "This is the application of all my knowledge" << endl;
    cout << "derived from studying the C++ Beginner's course" << endl;

    int choice;
    bool hasKey = false;

    // Game loop
    while (true) {
        cout << "You are in a room. What would you like to do?" << endl;
        cout << "1. Go forward" << endl;
        cout << "2. Search for treasure" << endl;
        cout << "3. Quit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        cout << endl;

        switch (choice) {
            case 1:
                if (!hasKey) {
                    cout << "You need a key to proceed!" << endl;
                    cout << endl;
                } else {
                    cout << "You unlocked the door and moved forward." << endl;
                    cout << endl;
                    // Simulate a battle
                    if (!battle()) {
                        cout << "Game Over!" << endl;
                        cout << endl;
                        return 0;
                    }
                    cout << "You continue your adventure..." << endl;
                    cout << endl;
                }
                break;
            case 2:
                cout << "You found a key!" << endl;
                cout << endl;
                hasKey = true;
                break;
            case 3:
                cout << "Thanks for playing daGame!" << endl;
                cout << endl;
                return 0;
            default:
                cout << "Invalid choice. Please try again." << endl;
                cout << endl;
        }
    }

    return 0;
}
