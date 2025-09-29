#ifndef AGGRESSIVESTRATEGY_H_
#define AGGRESSIVESTRATEGY_H_

#include "Strategy.h"
#include <iostream>

class AggressiveStrategy : public Strategy {
public:
    void execute() const override {
        cout << "Executing aggressive strategy!" << endl;
    }
};

#endif 
