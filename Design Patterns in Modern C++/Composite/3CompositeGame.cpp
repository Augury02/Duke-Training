#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <random>
#include <vector>
#include <memory>

using namespace std;

// Function prototype for enemyCast
int enemyCast();


/*
You'll see here that insted of initiating these values inside
the CombatEncounter interface, I already defined the term Attack
as a compound class, with the actual attacks being subclasses.
I also optimized the way that Enemy damage is calculated via a
vector; since they use similar damage computations but only with
varying values, this removes a lot of redundancies that I had
from the initial copy. On the topic of vectors, the player attack
is also now selected via a vector, improving on the previous if/else
logic basis from cin >> playerInput.
*/
class Attack {
public:
    virtual ~Attack() = default;
    virtual int execute() const = 0;
    virtual string getName() const = 0;
};
//PlayerAttack damage calculations
class BasicAttack : public Attack {     //This is the BasicAttack
public:
    int execute() const override {
        random_device rd; 
        mt19937 eng(rd()); 
        uniform_int_distribution<> distr(15, 25); 
        return distr(eng);
    }

    string getName() const override {
        return "Basic Attack";
    }
};

class LightningStrike : public Attack {     //Lightning Strike
public:
    int execute() const override {
        int damageSum = 0;
        for(int i = 0; i < 3; ++i) {
            random_device rd; 
            mt19937 eng(rd()); 
            uniform_int_distribution<> distr(25, 40); 
            damageSum += distr(eng);
        }
        return damageSum;
    }

    string getName() const override {
        return "Lightning Strike";
    }
};

class GambleAttack : public Attack {
public:
    int execute() const override {
        random_device rd; 
        mt19937 eng(rd()); 
        uniform_int_distribution<> distr(5, 80); 
        return distr(eng);
    }

    string getName() const override {
        return "Gamble Attack";
    }
};

class EnemyAttack : public Attack {
private:
    string name;
    int minDamage;
    int maxDamage;
public:
    EnemyAttack(string name, int minDamage, int maxDamage) 
        : name(name), minDamage(minDamage), maxDamage(maxDamage) {}

    int execute() const override {
        random_device rd;
        mt19937 eng(rd());
        uniform_int_distribution<> distr(minDamage, maxDamage);
        return distr(eng);
    }

    string getName() const override {
        return name;
    }
};

//Combat Encounter Simulation
bool battle() {
    int playerHealth = 100;
    int monsterHealth = 500;
    int playerInput;

    vector<shared_ptr<Attack>> playerAttacks = {
        make_shared<BasicAttack>(),
        make_shared<LightningStrike>(),
        make_shared<GambleAttack>()
    };
    /*
    This is the vector of player options/attacks, the values 
    are already stored from when I defined the classes/subclasses
    */
    
    vector<shared_ptr<Attack>> monsterAttacks = {
        make_shared<EnemyAttack>("NOTHING ON MY SIDE", 10, 15),
        make_shared<EnemyAttack>("MINE TOO", 15, 30),
        make_shared<EnemyAttack>("OKAY GUYS, THAT'S A WRAP", 10, 15)
    };
    /*
    This is the vector of monster attacks, I only defined one attack
    calculation, but with varying values which could be seen within the
    parenthesis, it also includes the attack name corresponding to the values
    */

    cout << endl;
    cout << "A wild monster appears!" << endl;

    while (playerHealth > 0 && monsterHealth > 0) {
        //Interface of Player Turn
        cout << "Your turn - Choose your action (1-3):" << endl;
        for (size_t i = 0; i < playerAttacks.size(); ++i) {
            cout << i + 1 << ". " << playerAttacks[i]->getName() << endl;
        }
        cout << endl;
        cin >> playerInput;        
        /*
        The interface itself has been changed to only show ability name
        which derives its name from the vector too, streamlining the code for the
        interface itself.

        This is still the same player action determinant, 
        but you'd also see here that the cout << for the damage screen
        has now been streamlined thanks to the integration of the vector, 
        I did not have to re-define these per playerInput value
        because the name of the playerAttack could already be accessed.
        */

        if (playerInput >= 1 && playerInput <= static_cast<int>(playerAttacks.size())) {
            int damage = playerAttacks[playerInput - 1]->execute();
            cout << "You've dealt " << damage << " damage using " << playerAttacks[playerInput - 1]->getName() << endl;
            monsterHealth -= damage;
            cout << "Enemy Health remaining: " << monsterHealth << endl;
            cout << endl;
        } else {
            cout << "Invalid action. Turn skipped." << endl;
            continue;
        }
        
        // Check if monster is defeated
        if (monsterHealth <= 0) {
            cout << "You defeated the monster!" << endl;
            return true;
        }

        // Monster's turn
        int monsterAction = enemyCast();
        if (monsterAction >= 1 && monsterAction <= static_cast<int>(monsterAttacks.size())) {
            int monsterAttack = monsterAttacks[monsterAction - 1]->execute();
            cout << "The enemy used '" << monsterAttacks[monsterAction - 1]->getName() << "' dealing " << monsterAttack << " damage" << endl;
            playerHealth -= monsterAttack;
        }
        /*
        You'll see here that a lot of redundancies have been removed
        thanks to the use of vector; this is where I repeatedly initiated
        a randomizer sequence with varying min max values per enemyCast value
        */

        cout << endl;
        cout << "Monster attacks! You received damage." << endl;
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
int enemyCast() {
    random_device rd;
    mt19937 eng(rd());
    uniform_int_distribution<> distr(1, 3);
    int rand = distr(eng);
    if (rand == 1) {
        cout << "PREPARE YOURSELF" << endl;
    }
    return rand;
}

int main() {        //Main function remains unchanged
    srand(time(0));

    cout << "Welcome to daGame!" << endl;

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
