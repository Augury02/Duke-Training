#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main() {

	fstream outFile;
	string outputFileName = "starWars.txt";
	outFile.open(outputFileName, ios::out);

	if(outFile.is_open()) {
        outFile << "///////////////////////" << endl;
        outFile << "" << endl;
        outFile << "Anakin: YOU TURNED HER AGAINST ME!?" << endl;
        outFile << "Obi Wan: You have done that yourself." << endl;
        outFile << "(He glares at his former master as he decloaks, with Obi Wan doing the same.)" << endl;
        outFile << "Anakin: YOU WILL NOT TAKE HER FROM ME!!!" << endl;
        outFile << "Obi Wan: Your anger and your lust for power have already done that." << endl;
        outFile << "Obi Wan: You have allowed this dark lord to twist your mind until now...." << endl;
        outFile << "until now, you have become the very thing you swore to destroy." << endl;
        outFile << "Anakin: Don't lecture me, Obi-Wan; I see through the lies of the Jedi..." << endl;
        outFile << "I do not fear the dark side as you do!" << endl;
		outFile.close();
	}
	else {
		cout << "May the force be with you " << outputFileName << endl;
	}

	return 0;
}
