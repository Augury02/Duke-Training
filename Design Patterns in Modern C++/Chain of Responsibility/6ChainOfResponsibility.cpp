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

// Decorator base class
class AttackDecorator : public Attack {
protected:
    shared_ptr<Attack> wrappedAttack;
public:
    AttackDecorator(shared_ptr<Attack> attack) : wrappedAttack(move(attack)) {}
    virtual ~AttackDecorator() = default;

    int execute() const override {
        return wrappedAttack->execute();
    }

    string getName() const override {
        return wrappedAttack->getName();
    }
};

// Concrete decorators using Chain of Responsibility
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
            damage *= 2;
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
        int fireDamage = distr(eng);
        cout << "Fire Damage: " << fireDamage << endl;
        return damage + fireDamage;
    }

    string getName() const override {
        return wrappedAttack->getName() + " with Fire Damage";
    }
};

// Monster Interface
class Monster {
public:
    virtual ~Monster() = default;
    virtual string getName() const = 0;
    virtual int getHealth() const = 0;
    virtual vector<shared_ptr<Attack>> getAttacks() const = 0;
};

// Concrete Monsters
class Margit : public Monster {
public:
    string getName() const override {
        return "Margit the Fell Omen";
    }

    int getHealth() const override {
        return 100;
    }

    vector<shared_ptr<Attack>> getAttacks() const override {
        return {
            make_shared<EnemyAttack>("Dagger Slash", 10, 20),
            make_shared<EnemyAttack>("Hammer Slam", 20, 30)
        };
    }
};

class Radahn : public Monster {
public:
    string getName() const override {
        return "Starscourge Radahn";
    }

    int getHealth() const override {
        return 300;
    }

    vector<shared_ptr<Attack>> getAttacks() const override {
        return {
            make_shared<EnemyAttack>("Gravity Arrow", 15, 40),
            make_shared<EnemyAttack>("Starcaller Cry", 25, 60),
            make_shared<EnemyAttack>("Meteor Crash", 0, 100)
        };
    }
};

class Malenia : public Monster {
public:
    string getName() const override {
        return "Malenia, Blade of Miquella";
    }

    int getHealth() const override {
        return 500;
    }

    vector<shared_ptr<Attack>> getAttacks() const override {
        return {
            make_shared<EnemyAttack>("Waterfowl Dance", 20, 50),
            make_shared<EnemyAttack>("Scarlet Rot", 10, 25)
        };
    }
};

// Monster Proxy
class MonsterProxy : public Monster {
private:
    shared_ptr<Monster> realMonster;

    shared_ptr<Monster> createRandomMonster() {
        random_device rd;
        mt19937 eng(rd());
        uniform_int_distribution<> distr(1, 3);
        int monsterType = distr(eng);

        switch(monsterType) {
            case 1: return make_shared<Margit>();
            case 2: return make_shared<Radahn>();
            case 3: return make_shared<Malenia>();
            default: return make_shared<Margit>();
        }
    }

public:
    MonsterProxy() : realMonster(createRandomMonster()) {}

    string getName() const override {
        return realMonster->getName();
    }

    int getHealth() const override {
        return realMonster->getHealth();
    }

    vector<shared_ptr<Attack>> getAttacks() const override {
        return realMonster->getAttacks();
    }
};

// Combat Encounter Simulation
bool battle() {
    int playerHealth = 100;
    int monsterHealth;
    int playerInput;
    int enhanceInput;

    MonsterProxy monster;
    monsterHealth = monster.getHealth();

    vector<shared_ptr<Attack>> playerAttacks = {
        make_shared<BasicAttack>(),
        make_shared<LightningStrike>(),
        make_shared<GambleAttack>()
    };

    vector<shared_ptr<Attack>> monsterAttacks = monster.getAttacks();

    cout << endl;
    cout << "A wild " << monster.getName() << " appears!" << endl;
    cout << "(Enemy HP: " << monster.getHealth() << ") " << endl;

    while (playerHealth > 0 && monsterHealth > 0) {
        // Interface of Player Turn
        cout << "Your turn - Choose your action (1-4):" << endl;
        for (size_t i = 0; i < playerAttacks.size(); ++i) {
            cout << i + 1 << ". " << playerAttacks[i]->getName() << endl;
        }
        cout << playerAttacks.size() + 1 << ". Use Estus Flask" << endl;
        cout << endl;
        cin >> playerInput;

        if (playerInput >= 1 && playerInput <= static_cast<int>(playerAttacks.size())) {
            shared_ptr<Attack> chosenAttack = playerAttacks[playerInput - 1];

            // Option to apply critical hit
            cout << "Do you want to enhance with Critical Hit? (1 for Yes, 0 for No): ";
            cin >> enhanceInput;
            if (enhanceInput == 1) {
                chosenAttack = make_shared<CriticalHitDecorator>(chosenAttack);
            }

            // Option to apply fire damage
            cout << "Do you want to enhance with Fire Damage? (1 for Yes, 0 for No): ";
            cin >> enhanceInput;
            if (enhanceInput == 1) {
                chosenAttack = make_shared<FireDamageDecorator>(chosenAttack);
            }

            /*
            This dynamic decision-making aligns with the Chain of Responsibility pattern's 
            idea of passing a request (in this case, enhancing an attack) through a chain of potential 
            handlers (decorators)
            */
            int damage = chosenAttack->execute();
            cout << "You've dealt " << damage << " damage using " << chosenAttack->getName() << endl;
            monsterHealth -= damage;
            cout << "Enemy Health remaining: " << monsterHealth << endl;
            cout << endl;
        } else if (playerInput == static_cast<int>(playerAttacks.size()) + 1) {
            random_device rd;
            mt19937 eng(rd());
            uniform_int_distribution<> distr(1, 100);
            int healChance = distr(eng);
            if (healChance <= 70) { // 70% chance of healing
                uniform_int_distribution<> healDistr(20, 40);
                int healAmount = healDistr(eng);
                playerHealth += healAmount;
                cout << "You used Estus Flask and healed for " << healAmount << " health." << endl;
                cout << "Player Health: " << playerHealth << endl;
                cout << "Monster does not attack this turn." << endl;
                continue;
            } else {
                cout << "You used Estus Flask, but it failed." << endl;
            }
        } else {
            cout << "Invalid action. Turn skipped." << endl;
            continue;
        }

        // Check if monster is defeated
        if (monsterHealth <= 0) {
            cout << "You defeated the " << monster.getName() << "!" << endl;
            return true;
        }

        // Monster's turn
        int monsterAction = enemyCast();
        if (monsterAction >= 1 && monsterAction <= static_cast<int>(monsterAttacks.size())) {
            int monsterAttack = monsterAttacks[monsterAction - 1]->execute();
            cout << "The " << monster.getName() << " used '" << monsterAttacks[monsterAction - 1]->getName() << "' dealing " << monsterAttack << " damage" << endl;
            playerHealth -= monsterAttack;  
        }

        cout << endl;
        cout << "Monster attacks! You received damage." << endl;
        cout << "Player Health remaining: " << playerHealth << endl;
        cout << endl;

        // Check if player is defeated
        if (playerHealth <= 0) {
            cout << "You were defeated by the " << monster.getName() << "!" << endl;
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
        cout << "The enemy is preparing to attack!" << endl;
    }
    return rand;
}

int main() {
    srand(time(0));

    cout << "Welcome to discount Elden Ring!" << endl;

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
