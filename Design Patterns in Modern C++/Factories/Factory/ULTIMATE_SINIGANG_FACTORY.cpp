#include <iostream>
#include <string>
#include <memory> // for std::unique_ptr
using namespace std;

// Base class
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
    }
    void cook() const {
        cout << "Preparing " << sourFruit_ << " . . . " << endl;
        cout << "Extracting sourness . . ." << endl;
        cout << "Adding " << meat_ << " . . ." << endl;
        cout << "Boiling broth . . ." << endl;
        cout << "Adding " << vegetable1_<< " . . . " << endl;
        cout << "Adding " << vegetable2_<< " . . . " << endl;
        cout << "Let simmer . . ." << endl;
        cout << "Congrats, you may now plate and serve your " << description_ << "!!" << endl;
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

// Concrete Builder for Sinigang Sa Bayabas
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

// Concrete Builder for Sinigang Sa Sampalok
class SinigangSaSampalokBuilder : public SinigangBuilder {
public:
    void buildSour() override {
        sinigang_->setSourFruit("Sampalok");
    }
    void buildMeat() override {
        sinigang_->setMeat("Beef");
    }
    void buildVegetable1() override {
        sinigang_->setVegetable1("Sitaw");
    }
    void buildVegetable2() override {
        sinigang_->setVegetable2("Talong");
    }
    Sinigang* getSinigang() override {
        return sinigang_;
    }
    SinigangSaSampalokBuilder() : sinigang_(new Sinigang()) {}
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

// SinigangFactory class
class SinigangFactory {
public:
    static Sinigang* createSinigang(const std::string& type) {
        if (type == "SinigangSaBayabas") {
            SinigangSaBayabasBuilder builder;
            Cook cook;
            cook.makeSinigang(&builder);
            Sinigang* sinigang = builder.getSinigang();
            sinigang->setDescription("Sinigang Sa Bayabas");
            return sinigang;
        } else if (type == "SinigangSaSampalok") {
            SinigangSaSampalokBuilder builder;
            Cook cook;
            cook.makeSinigang(&builder);
            Sinigang* sinigang = builder.getSinigang();
            sinigang->setDescription("Sinigang Sa Sampalok");
            return sinigang;
        } else {
            return nullptr;
        }
    }
};

int main() {
    Sinigang* sinigang1 = SinigangFactory::createSinigang("SinigangSaBayabas");
    cout << "   " << endl;
    sinigang1->display();
    cout << "   " << endl;
    cout << "   " << endl;
    cout << "Preparing Cooking Process: " << endl;
    sinigang1->cook(); 
    delete sinigang1;

    Sinigang* sinigang2 = SinigangFactory::createSinigang("SinigangSaSampalok");
    cout << "   " << endl;
    sinigang2->display();
    cout << "   " << endl;
    cout << "   " << endl;
    cout << "Preparing Cooking Process: " << endl;
    sinigang2->cook();
    delete sinigang2;

    return 0;
}
