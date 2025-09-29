#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <random>
#include <vector>
#include <memory>

using namespace std;

// Forward declarations
class Attack {
public:
    virtual ~Attack() = default;
    virtual int execute() const = 0;
    virtual string getName() const = 0;
};

class Command {
public:
    virtual ~Command() = default;
    virtual void execute() = 0;
};

class AttackCommand : public Command {
private:
    shared_ptr<Attack> attack;
    int enhanceOption; // 0 for none, 1 for critical hit, 2 for fire damage

public:
    AttackCommand(shared_ptr<Attack> attack, int enhanceOption)
        : attack(move(attack)), enhanceOption(enhanceOption) {}

    void execute() override {
        int damage = attack->execute();
        if (enhanceOption == 1) {
            damage *= 2; // Critical hit
            cout << "Critical Hit!" << endl;
        } else if (enhanceOption == 2) {
            random_device rd;
            mt19937 eng(rd());
            uniform_int_distribution<> distr(5, 15);
            int fireDamage = distr(eng);
            damage += fireDamage;
            cout << "Fire Damage: " << fireDamage << endl;
        } else if (enhanceOption == 3) {
            random_device rd;
            mt19937 eng(rd());
            uniform_int_distribution<> distr(5, 15);
            int fireDamage = distr(eng);
            damage += fireDamage;
            damage *= 2;
            cout << "Fire Damage: " << fireDamage << endl;
            cout << "Critical Hit!" << endl;
        }
        cout << "You've dealt " << damage << " damage using " << attack->getName() << endl;
    }
};

class PlayerTurn {
private:
    vector<shared_ptr<Attack>> attacks;
    int playerInput;
    int enhanceInput;

public:
    PlayerTurn(const vector<shared_ptr<Attack>>& attacks) : attacks(attacks) {}

    void execute() {
        cout << "Your turn - Choose your action (1-" << attacks.size() << "):" << endl;
        for (size_t i = 0; i < attacks.size(); ++i) {
            cout << i + 1 << ". " << attacks[i]->getName() << endl;
        }
        cout << attacks.size() + 1 << ". Use Estus Flask" << endl;
        cout << endl;
        cin >> playerInput;

        if (playerInput >= 1 && playerInput <= static_cast<int>(attacks.size())) {
            cout << "Determine attack enhancements? (0 = No enhancement; 1 = Crit; 2 = Fire; 3 = Both)): ";
            cin >> enhanceInput;

            Command* command;
            if (enhanceInput == 1) {
                command = new AttackCommand(attacks[playerInput - 1], 1); // Enhance with critical hit
            } else if (enhanceInput == 2) {
                command = new AttackCommand(attacks[playerInput - 1], 2); // Enhance with fire damage
            } else if (enhanceInput == 3) {
                command = new AttackCommand(attacks[playerInput - 1], 3); // Enhance with both fire damage and critical hit
            } else {
                command = new AttackCommand(attacks[playerInput - 1], 0); // No enhancement
            }

            command->execute();
            delete command;
        } else if (playerInput == static_cast<int>(attacks.size()) + 1) {
            random_device rd;
            mt19937 eng(rd());
            uniform_int_distribution<> distr(1, 100);
            int healChance = distr(eng);
            if (healChance <= 70) { // 70% chance of healing
                uniform_int_distribution<> healDistr(20, 40);
                int healAmount = healDistr(eng);
                cout << "You used Estus Flask and healed for " << healAmount << " health." << endl;
            } else {
                cout << "You used Estus Flask, but it failed." << endl;
            }
        } else {
            cout << "Invalid action. Turn skipped." << endl;
        }
    }
};

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

class Monster {
public:
    virtual ~Monster() = default;
    virtual string getName() const = 0;
    virtual int getHealth() const = 0;
    virtual vector<shared_ptr<Attack>> getAttacks() const = 0;
};

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

bool battle() {
    int playerHealth = 100;
    int monsterHealth;

    MonsterProxy monster;
    monsterHealth = monster.getHealth();

    vector<shared_ptr<Attack>> playerAttacks = {
        make_shared<BasicAttack>(),
        make_shared<LightningStrike>(),
        make_shared<GambleAttack>()
    };

    vector<shared_ptr<Attack>> monsterAttacks = monster.getAttacks();

    cout << endl;
    cout << monster.getName() << " appears!" << endl;
    cout << "(Enemy HP: " << monster.getHealth() << ") " << endl;

    while (playerHealth > 0 && monsterHealth > 0) {
        PlayerTurn playerTurn(playerAttacks);
        playerTurn.execute();

        // Check if player is defeated
        if (playerHealth <= 0) {
            cout << "You were defeated by the " << monster.getName() << "!" << endl;
            return false;
        }

        // Monster's turn
        random_device rd;
        mt19937 eng(rd());
        uniform_int_distribution<> distr(1, monsterAttacks.size());
        int monsterAction = distr(eng);

        int monsterAttack = monsterAttacks[monsterAction - 1]->execute();
        cout << monster.getName() << " used '" << monsterAttacks[monsterAction - 1]->getName() << "' dealing " << monsterAttack << " damage" << endl;
        playerHealth -= monsterAttack;  

        // Check if monster is defeated
        if (monsterHealth <= 0) {
            cout << "You defeated " << monster.getName() << "!" << endl;
            return true;
        }

        cout << "Monster attacks! You received damage." << endl;
        cout << "Player Health remaining: " << playerHealth << endl;
        cout << endl;
    }
    return false;
}

//Additional features added within the exploration phase
void explore(int& playerHealth, bool& hasKey) {
    int choice;
    random_device rd;
    mt19937 eng(rd());
    uniform_int_distribution<> eventDistr(1, 5);

    int event = eventDistr(eng);

    switch (event) {
        case 1:
            cout << "You find a chest! Do you want to open it? (1 = Yes, 2 = No): ";
            cin >> choice;
            if (choice == 1) {
                cout << "You found a health potion. You gain 30 health." << endl;
                playerHealth += 30;
            } else {
                cout << "You decide not to open the chest." << endl;
            }
            break;
        case 2:
            cout << "You encounter a friendly NPC. They give you a key!" << endl;
            hasKey = true;
            break;
        case 3:
            cout << "You stumble upon a hidden shortcut. Do you want to take it? (1 = Yes, 2 = No): ";
            cin >> choice;
            if (choice == 1) {
                cout << "You take the shortcut and avoid a dangerous path." << endl;
            } else {
                cout << "You decide to continue on the current path." << endl;
            }
            break;
        case 4:
            cout << "You sense danger nearby. You can proceed cautiously or retreat. What will you do? (1 = Proceed, 2 = Retreat): ";
            cin >> choice;
            if (choice == 1) {
                cout << "You proceed cautiously and avoid the danger." << endl;
            } else {
                cout << "You decide to retreat to a safer location." << endl;
            }
            break;
        case 5:
            cout << "You find an ancient artifact. It's very valuable!" << endl;
            break;
        default:
            cout << "You continue exploring..." << endl;
            break;
    }

    cout << endl;
}

int main() {
    srand(time(0));

    cout << "Welcome to discount Elden Ring!" << endl;

    int choice;
    bool hasKey = false;
    int playerHealth = 100;

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
                    // Simulate exploration events
                    explore(playerHealth, hasKey);

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
                cout << "You search for treasure..." << endl;
                explore(playerHealth, hasKey);
                break;
            case 3:
                cout << "Thanks for playing discount Elden Ring!" << endl;
                cout << endl;
                return 0;
            default:
                cout << "Invalid choice. Please try again." << endl;
                cout << endl;
        }
    }

    return 0;
}

