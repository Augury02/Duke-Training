#include <iostream>
#include <vector>
#include <string>
#include <typeinfo>
#include <initializer_list>		//Initializer List
#include "Biogesic.h"			//Practiced header file modification; Nested Template Classes; Making Classes Iterable
using namespace std; 			//Took Sir Charles' advice of changing names so I could explore how things work

/*
Not much application was found for decltype
Not much application was found for C++98; C++11 for this code
*/

struct Diatabs{				//Application of Initializer list and structures
	public:
	Diatabs(initializer_list<string> loperamide)
	{
		for(auto value : loperamide)
		{ cout << value << endl; }
	}
};

int main() {
	auto initialize = {"THE BOAT IS SINKING", "GET YOUR LIFE JACKETS", "4 LIFE JACKETS REMAIN"};	//Usage of auto
	for (auto beginText : initialize)	//Range based loops
	{
		cout << beginText << endl;
	}
	cout << "" << endl;
	cout << "" << endl;

	auto countdown = {5, 4, 3, 2, 1};
	for (auto beginText : countdown)
	{
		cout << beginText << ". . ." << endl;
	}


	cout << "" << endl;
	cout << "" << endl;
	Biogesic<string>::iterator it;
	it.print();

	Biogesic<string> TheBoatIsSinking(5);
	TheBoatIsSinking.add("Sir Charles");				//Will get overwritten by Sir Richard
	TheBoatIsSinking.add("Sir Neil");
	TheBoatIsSinking.add("Sir Andrei");
	TheBoatIsSinking.add("Sir Ivanne");
	TheBoatIsSinking.add("Sir Charles drowned");		//By Experimenting, figured out that Sir Richard will replace Sir Charles and take its place order
	TheBoatIsSinking.add("Sir Richard");				//Therefore I must put the drowned cout on the 5th place rather than last

	/*
	Otherwise, terminal output will be:
	Sir Charles drowned
	Sir Neil
	Sir Andrei
	Sir Ivanne
	Sir Richard
	*/

	for(auto i =0; i < TheBoatIsSinking.size(); i++)
	{
		cout << TheBoatIsSinking.get(i) << endl;
	}

	Diatabs constipation{"gege bawi next lyf"};	
	Diatabs diarrhea{"jk", "tnx", "sa", "tips", "sir"};		//because there's an "endl;" in the original structure, each element enters a new space

	string snobber;
	decltype(snobber) name = "-Ynah";				//Application of decltype, type id and name mangling
	cout << name << endl;
	cout << typeid(snobber).name() << endl;
	return 0;
}