#include <iostream>
#include "AggressiveStrategy.h"
#include "DefensiveStrategy.h"
#include "Commander.h"
#include "Soldier.h"

int main() {
    cout << "Starting program . . . " << std::endl;

    //New objects under the subclasses of IMPLEMENTOR Strategy
    Strategy* aggressive = new AggressiveStrategy();
    Strategy* defensive = new DefensiveStrategy();

    //New objects under the subclass of ABSTRACTION Troops
    Troops* soldier = new Soldier(aggressive);
    Troops* commander = new Commander(defensive);

    // Execute the fight function, demonstrating the Bridge Pattern
    soldier->fight();    // Soldier using aggressive strategy
    commander->fight();  // Commander using defensive strategy

    delete soldier;
    delete commander;

    return 0;
}


/*
Troop class acts as the abstraction
Strategy interface along with its concrete implementations 
provide the implementation
This decouples the specific behavior (strategy) from the types of troops,
 allowing both to vary independently
*/