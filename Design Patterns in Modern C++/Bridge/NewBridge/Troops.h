#ifndef TROOPS_H_
#define TROOPS_H_

#include "Strategy.h"
using namespace std;

class Troops {
protected:
    Strategy* strategy;         // Bridge to the implementor (strategy)
public:
    Troops(Strategy* strat) : strategy(strat) {}
    virtual ~Troops() { delete strategy; }
    virtual void fight() const = 0;
};

#endif 
