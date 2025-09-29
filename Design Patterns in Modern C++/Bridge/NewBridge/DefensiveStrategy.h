#ifndef DEFENSIVESTRATEGY_H_
#define DEFENSIVESTRATEGY_H_

#include "Strategy.h"
#include <iostream>

class DefensiveStrategy : public Strategy {
public:
    void execute() const override {
        cout << "Executing defensive strategy!" << endl;
    }
};

#endif 
