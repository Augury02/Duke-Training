#ifndef STRATEGY_H_
#define STRATEGY_H_

class Strategy {
public:
    virtual void execute() const = 0;
    virtual ~Strategy() = default;
};

#endif 
