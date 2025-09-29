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

class Attack {
public:
    virtual ~Attack() = default;
    virtual int execute() const = 0;
    virtual string getName() const = 0;
};

// Basic Attack types
class BasicAttack : public Attack {
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

class LightningStrike : public Attack {
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

// Enemy attack
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

// Decorator base class; subclass of Attack
/*
the application of a decorator in this code lies on enhancing the functionality of the attack class
and its subclasses (BasicAttack, LightningStrike, etc.) without altering their structure
the application of either decorator subclasses (CriticalHitDecorator & FireDamageDecorator) 
adds responsibilities to other objects dynamically (there is a check condition for a
crit in every instance of attack, however for this demonstration, they apply in every
attack instance)
*/
class AttackDecorator : public Attack {
protected:
    shared_ptr<Attack> wrappedAttack;   
    /*
    when a player chooses an attack, it is wrapped in both CriticalHitDecorator and FireDamageDecorator 
    this enhances the selected attack with the additional functionalities
    */ 
public:
    AttackDecorator(shared_ptr<Attack> attack) : wrappedAttack(move(attack)) {}
    virtual ~AttackDecorator() = default;
};

// Concrete decorators
class CriticalHitDecorator : public AttackDecorator {   
public:
    CriticalHitDecorator(shared_ptr<Attack> attack) : AttackDecorator(move(attack)) {}

    int execute() const override {
        int damage = wrappedAttack->execute();
        random_device rd; 
        mt19937 eng(rd()); 
        uniform_int_distribution<> distr(1, 100); 
        if (distr(eng) <= 20) { // 20% chance of a critical hit
            cout << "Critical Hit!" << endl;
            damage *= 2;            //CriticalHit doubles the damage
        }
        return damage;
    }

    string getName() const override {
        return wrappedAttack->getName() + " with Critical Hit";
    }
};

class FireDamageDecorator : public AttackDecorator {
public:
    FireDamageDecorator(shared_ptr<Attack> attack) : AttackDecorator(move(attack)) {}

    int execute() const override {
        int damage = wrappedAttack->execute();
        random_device rd; 
        mt19937 eng(rd()); 
        uniform_int_distribution<> distr(5, 15); 
        int fireDamage = distr(eng);        //additional fire damage is randomly generated between 5-15
        cout << "Fire Damage: " << fireDamage << endl;
        return damage + fireDamage;
    }

    string getName() const override {
        return wrappedAttack->getName() + " with Fire Damage";
    }
};

// Combat Encounter Simulation
bool battle() {
    int playerHealth = 100;
    int monsterHealth = 500;
    int playerInput;

    vector<shared_ptr<Attack>> playerAttacks = {
        make_shared<BasicAttack>(),
        make_shared<LightningStrike>(),
        make_shared<GambleAttack>()
    };

    vector<shared_ptr<Attack>> monsterAttacks = {
        make_shared<EnemyAttack>("NOTHING ON MY SIDE", 10, 15),
        make_shared<EnemyAttack>("MINE TOO", 15, 30),
        make_shared<EnemyAttack>("OKAY GUYS, THAT'S A WRAP", 10, 15)
    };

    cout << endl;
    cout << "A wild monster appears!" << endl;

    while (playerHealth > 0 && monsterHealth > 0) {
        // Interface of Player Turn
        cout << "Your turn - Choose your action (1-3):" << endl;
        for (size_t i = 0; i < playerAttacks.size(); ++i) {
            cout << i + 1 << ". " << playerAttacks[i]->getName() << endl;
        }
        cout << endl;
        cin >> playerInput;

        if (playerInput >= 1 && playerInput <= static_cast<int>(playerAttacks.size())) {
            shared_ptr<Attack> chosenAttack = playerAttacks[playerInput - 1];

            // Apply decorators (for demonstration purposes, we apply both)
            chosenAttack = make_shared<CriticalHitDecorator>(chosenAttack);
            chosenAttack = make_shared<FireDamageDecorator>(chosenAttack);

            int damage = chosenAttack->execute();
            cout << "You've dealt " << damage << " damage using " << chosenAttack->getName() << endl;
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

int main() { 
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
