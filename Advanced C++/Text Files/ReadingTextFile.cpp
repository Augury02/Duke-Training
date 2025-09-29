#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

int main() {

	string inFileName = "starWars.txt";

	ifstream inFile;

	inFile.open(inFileName);

	if (inFile.is_open()) {

		string line;

		while (inFile) {
			getline(inFile, line);
			cout << line << endl;
		}

		inFile.close();
	} else {
		cout << "Cannot open file: " << inFileName << endl;
	}

	return 0;
}