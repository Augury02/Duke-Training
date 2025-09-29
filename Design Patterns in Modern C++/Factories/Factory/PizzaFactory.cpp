#include <iostream>
#include <string>

using namespace std;

enum class PizzaType // used to specify how the point coordinates should be interpreted
{
  hawaiian,
  newyork,
  fourcheese, 
  allmeat
};

class Pizza
{
    Pizza(string toppings1, string toppings2) : toppings1(toppings1), toppings2(toppings2){}
    public:
    string toppings1, toppings2;

    friend class PizzaFactory;
};

class PizzaFactory
{
    public:
    static Pizza NewHawaiian(string pineapple, string cheese){
        return Pizza{ pineapple, cheese };
    }

    /*Actual string name "string pineapple" for example, has no bearing; the use of string and
    this particular usage does not show well the variety, since this is not formulaic such that
    the return values and variables could change drastically. Instead the string names were just
    used as reference in defining the toppings within the int main*/

    static Pizza NewNY(string cheese, string pepperoni){
        return Pizza{ cheese, pepperoni };
    }

    static Pizza NewFourCheese(string cheese, string morecheese){
        return Pizza{ cheese, morecheese };
    }

    static Pizza NewAllMeat(string pork, string beef){
        return Pizza{ pork, beef };
    }

};


int main()
{
  Pizza pizza1 = PizzaFactory::NewHawaiian("Pineapple", "Cheese");
  cout << "Ordered: Hawaiian Pizza" << endl;
  cout << "Toppings: " << pizza1.toppings1 << ", " << pizza1.toppings2 << endl;
  cout << endl;

  Pizza pizza2 = PizzaFactory::NewNY("Cheese", "Pepperoni");
  cout << "Ordered: New York Style Pizza" << endl;
  cout << "Toppings: " << pizza2.toppings1 << ", " << pizza2.toppings2 << endl;
  cout << endl;

  Pizza pizza3 = PizzaFactory::NewFourCheese("Cheese", "MoreCheese");
  cout << "Ordered: Four Cheese Pizza" << endl;
  cout << "Toppings: " << pizza3.toppings1 << ", " << pizza3.toppings2 << endl;
  cout << endl;

  Pizza pizza4 = PizzaFactory::NewAllMeat("Pork", "Beef");
  cout << "Ordered: All Meat Pizza" << endl;
  cout << "Toppings: " << pizza4.toppings1 << ", " << pizza4.toppings2 << endl;
  cout << endl;

  return 0;
}
