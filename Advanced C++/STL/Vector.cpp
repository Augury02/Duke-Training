#include <iostream>
#include <map>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    multimap<string, string> genreHorror;

    genreHorror.insert(make_pair("Color out of space", "H.P. Lovecraft"));
    genreHorror.insert(make_pair("Black cat", "Edgar Allan Poe"));
    genreHorror.insert(make_pair("The Murders in the Rue Morgue", "Edgar Allan Poe"));
    genreHorror.insert(make_pair("Salem's Lot", "Stephen King"));
    genreHorror.insert(make_pair("The Oval Portrait", "Edgar Allan Poe"));
    genreHorror.insert(make_pair("The Dunwich Horror", "H.P. Lovecraft"));
    genreHorror.insert(make_pair("Pet Sematary", "Stephen King"));
    genreHorror.insert(make_pair("The Thing in the Doorstep", "H.P. Lovecraft"));



    cout << "How would you like your books sorted?" << endl;
    cout << "1. According to author" << endl;
    cout << "2. According to title" << endl;
    int menuInput;
    cin >> menuInput;

    if (menuInput == 1) {
        vector<pair<string, string>> sortedAuthors(genreHorror.begin(), genreHorror.end());
        sort(sortedAuthors.begin(), sortedAuthors.end(), [](const pair<string, string>& a, const pair<string, string>& b) {
            return a.second < b.second; 
        });

        for (const auto& pair : sortedAuthors) {
            cout << "Sorting according to author . . ." << endl;
            cout << "Author: " << pair.second << ", Title: " << pair.first << endl;
        }
    } else if (menuInput == 2) {
        
        for (auto it = genreHorror.begin(); it != genreHorror.end(); ++it) {
            cout << "Sorting according to book title . . ." << endl;
            cout << "Title: " << it->first << ", Author: " << it->second << endl;
        }
    } else {
        cout << "Entry not recognized" << endl;
    }

    return 0;
}
