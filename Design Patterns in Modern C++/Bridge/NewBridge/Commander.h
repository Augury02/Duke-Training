#ifndef COMMANDER_H_
#define COMMANDER_H_

#include "Troops.h"
#include <iostream>

class Commander : public Troops {
public:
    Commander(Strategy* strat) : Troops(strat) {}
    void fight() const override {
        cout << "Commander: ";
        strategy->execute();
    }
};

#endif 
