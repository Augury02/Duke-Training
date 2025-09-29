#include <string>
#include <iostream>
#include <sstream>
#include <memory>
using namespace std;

struct Classification
{
    string environment;
    string dietType;
    int noOfLegs;

    Classification(const string& environment, const string& dietType, const int noOfLegs)
        : environment{environment},
          dietType{dietType},
          noOfLegs{noOfLegs}
    {}

    friend ostream& operator<<(ostream& os, const Classification& obj)
    {
        return os
            << " || Environment: " << obj.environment
            << " || Diet Classification: " << obj.dietType
            << " || No. of Legs: " << obj.noOfLegs;
    }
};

// Abstract base class for Prototype pattern
class AnimalPrototype
{
public:
    virtual ~AnimalPrototype() = default;
    virtual unique_ptr<AnimalPrototype> clone() const = 0;
    virtual void print() const = 0;
};

// Concrete class inheriting from AnimalPrototype
class Animal : public AnimalPrototype
{
public:
    string name;
    Classification classification;

    Animal(const string& name, const Classification& classification)
        : name{name}, classification{classification}
    {}

    // Cloning process 
    unique_ptr<AnimalPrototype> clone() const override
    {
        return make_unique<Animal>(*this);
    }

    // Print method
    void print() const override
    {
        cout << "Animal: " << name << " " << classification << endl;
    }
};

int main()
{
    // Creating an original animal
    unique_ptr<AnimalPrototype> originalAnimal = make_unique<Animal>("Tiger", Classification("Forest", "Carnivore", 4));
    originalAnimal->print();

    // Creating entirely different animal; but using cloning process
    unique_ptr<AnimalPrototype> uniqueCloned = originalAnimal->clone();
    Animal* animalClone1 = static_cast<Animal*>(uniqueCloned.get());
    animalClone1->name = "Chicken";
    animalClone1->classification.environment = "Meadow";
    animalClone1->classification.dietType = "Omnivore";
    animalClone1->classification.noOfLegs = 2;
    uniqueCloned->print();

    // Creating another original animal, spider
    unique_ptr<AnimalPrototype> Arachnid1 = make_unique<Animal>("Spider", Classification("Every Habitat", "Insectivore", 8));
    Arachnid1->print();

    // Cloning Spider to make a sub-type, with some change in characteristics
    unique_ptr<AnimalPrototype> clonedAnimal1 = Arachnid1->clone();
    Animal* animalClone2 = static_cast<Animal*>(clonedAnimal1.get());
    animalClone2->name = "Orb Weaver Spider";
    animalClone2->classification.environment = "Tree-tops";
    clonedAnimal1->print();

    // 2nd clone
    unique_ptr<AnimalPrototype> clonedAnimal2 = Arachnid1->clone();
    Animal* animalClone3 = static_cast<Animal*>(clonedAnimal2.get());
    animalClone3->name = "Wolf Spider";
    animalClone3->classification.environment = "Tree barks/Surface";
    clonedAnimal2->print();

    return 0;
}
