#ifndef SOLDIER_H_
#define SOLDIER_H_

#include "Troops.h"
#include <iostream>

class Soldier : public Troops {
public:
    Soldier(Strategy* strat) : Troops(strat) {}
    void fight() const override {
        cout << "Soldier: ";
        strategy->execute();
    }
};

#endif 
