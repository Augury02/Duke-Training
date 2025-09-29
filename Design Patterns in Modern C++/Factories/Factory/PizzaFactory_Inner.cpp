#include <iostream>
#include <string>

using namespace std;

enum class PizzaType
{
    hawaiian,
    newyork,
    fourcheese,
    allmeat
};

class Pizza
{
    Pizza(string toppings1, string toppings2) : toppings1(toppings1), toppings2(toppings2) {}

public:
    string toppings1, toppings2;
    
    // Inner factory class
    class Factory           //class Factory is embedded within the base class Pizza
    {                       //therefore its call function is also directly from the Pizza class
    public:                 //instead of a separate class PizzaFactory
        static Pizza NewHawaiian(string pineapple, string cheese)
        {
            return Pizza{ pineapple, cheese };
        }

        static Pizza NewNY(string cheese, string pepperoni)
        {
            return Pizza{ cheese, pepperoni };
        }

        static Pizza NewFourCheese(string cheese, string morecheese)
        {
            return Pizza{ cheese, morecheese };
        }

        static Pizza NewAllMeat(string pork, string beef)
        {
            return Pizza{ pork, beef };
        }
    };
};

int main()
{
    Pizza pizza1 = Pizza::Factory::NewHawaiian("Pineapple", "Cheese");
    cout << "Ordered: Hawaiian Pizza" << endl;
    cout << "Toppings: " << pizza1.toppings1 << ", " << pizza1.toppings2 << endl;
    cout << endl;

    Pizza pizza2 = Pizza::Factory::NewNY("Cheese", "Pepperoni");
    cout << "Ordered: New York Style Pizza" << endl;
    cout << "Toppings: " << pizza2.toppings1 << ", " << pizza2.toppings2 << endl;
    cout << endl;

    Pizza pizza3 = Pizza::Factory::NewFourCheese("Cheese", "MoreCheese");
    cout << "Ordered: Four Cheese Pizza" << endl;
    cout << "Toppings: " << pizza3.toppings1 << ", " << pizza3.toppings2 << endl;
    cout << endl;

    Pizza pizza4 = Pizza::Factory::NewAllMeat("Pork", "Beef");
    cout << "Ordered: All Meat Pizza" << endl;
    cout << "Toppings: " << pizza4.toppings1 << ", " << pizza4.toppings2 << endl;
    cout << endl;

    // Using the inner factory to create a pizza
    Pizza pizza5 = Pizza::Factory::NewHawaiian("Extra Pineapple", "Double Cheese");
    cout << "Ordered: Custom Hawaiian Pizza" << endl;
    cout << "Toppings: " << pizza5.toppings1 << ", " << pizza5.toppings2 << endl;

    return 0;
}
