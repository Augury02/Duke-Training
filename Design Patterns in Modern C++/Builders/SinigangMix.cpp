#include <iostream>
#include <string>
using namespace std;

//Base class
class Sinigang {
public:
    void setSourFruit(const std::string& sourFruit) {
        sourFruit_ = sourFruit;
    }
    void setMeat(const std::string& meat) {
        meat_ = meat;
    }
    void setVegetable1(const std::string& vegetable1) {
        vegetable1_ = vegetable1;
    }
    void setVegetable2(const std::string& vegetable2) {
        vegetable2_ = vegetable2;
    }
    void setDescription(const std::string& description) {
        description_ = description;
    }
    void display() const {
        cout << "Sinigang type:  " << description_ << endl;
        cout << "Sour fruit: " << sourFruit_ << endl;
        cout << "Meat: " << meat_ << endl;
        cout << "Vegetable1: " << vegetable1_ << endl;
        cout << "Vegetable2: " << vegetable2_ << endl;
        //cout << "You've dealt " << basicAttackDamage << " using Basic Attack" << endl;  
        //SIMILAR TO THAT LINE OF CODE FROM CombatAbilities (SRP) source file
    }
    void cook() const{
        cout << "Preparing " << sourFruit_ << " . . . " << endl;
        cout << "Extracting sourness . . ." << endl;
        cout << "Adding " << meat_ << " . . ." << endl;
        cout << "Boiling broth . . ." << endl;
        cout << "Adding " << vegetable1_<< " . . . " << endl;
        cout << "Adding " << vegetable2_<< " . . . " << endl;
        cout << "Let simmer . . ." << endl;
        cout << "Congrats, you may now plate late and serve your " << description_ << "!!" << endl;
    }
private:
    string sourFruit_;
    string meat_;
    string vegetable1_;
    string vegetable2_;
    string description_;
};

// Builder interface
class SinigangBuilder {
public:
    virtual void buildSour() = 0;
    virtual void buildMeat() = 0;
    virtual void buildVegetable1() = 0;
    virtual void buildVegetable2() = 0;
    virtual Sinigang* getSinigang() = 0;
};

// Concrete Builder
class SinigangSaBayabasBuilder : public SinigangBuilder {
public:
    void buildSour() override {
        sinigang_->setSourFruit("Bayabas");
    }
    void buildMeat() override {
        sinigang_->setMeat("Pork");
    }
    void buildVegetable1() override {
        sinigang_->setVegetable1("Okra");
    }
    void buildVegetable2() override {
        sinigang_->setVegetable2("Kangkong");
    }
    Sinigang* getSinigang() override {
        return sinigang_;
    }
    SinigangSaBayabasBuilder() : sinigang_(new Sinigang()) {}
private:
    Sinigang* sinigang_;
};

// Director class (optional)
class Cook {
public:
    void makeSinigang(SinigangBuilder* builder) {
        builder->buildSour();
        builder->buildMeat();
        builder->buildVegetable1();
        builder->buildVegetable2();
    }
};

int main() {
    Cook cook;
    SinigangSaBayabasBuilder sinigangSaBayabasBuilder;
    
    cook.makeSinigang(&sinigangSaBayabasBuilder);
    Sinigang* sinigangSaBayabas = sinigangSaBayabasBuilder.getSinigang();
    sinigangSaBayabas->setDescription("Sinigang Sa Bayabas");
    cout << "   " << endl;
    sinigangSaBayabas->display();
    cout << "   " << endl;
    cout << "   " << endl;
    cout << "Preparing Cooking Process: " << endl;
    sinigangSaBayabas->cook(); // Call the cook() method to demonstrate cooking process

    delete sinigangSaBayabas;

    return 0;
}