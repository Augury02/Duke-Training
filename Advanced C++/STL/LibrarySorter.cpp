#include <iostream>
#include <map>
#include <vector>
#include <algorithm>
#include <cstdlib>
using namespace std;

//HEADER
int showMenu();
void processSelection(int option);

//MAIN
int main() {
    cin.ignore();
    system("cls");      
    int selection;
    do {
        selection = showMenu();
        processSelection(selection);
        
    } while (selection != 4);

    return 0;
}

//SOURCE
int showMenu() {
    cout << "Select book genre (1-4):" << endl;
    cout << "1. Horror" << endl;
    cout << "2. Poetry" << endl;
    cout << "3. Fantasy" << endl;
    cout << "4. Exit" << endl;
    cout << "Input your selection: ";
    int menuInput;
    cin >> menuInput;
    return menuInput;
}

void processSelection(int option) {
    multimap<string, string> genreHorror;
    multimap<string, string> genrePoetry;
    multimap<string, string> genreFantasy;
    switch (option) {
    case 1:
        genreHorror.insert(make_pair("Color out of space", "H.P. Lovecraft"));
        genreHorror.insert(make_pair("Black cat", "Edgar Allan Poe"));
        genreHorror.insert(make_pair("The Murders in the Rue Morgue", "Edgar Allan Poe"));
        genreHorror.insert(make_pair("Salem's Lot", "Stephen King"));
        genreHorror.insert(make_pair("The Oval Portrait", "Edgar Allan Poe"));
        genreHorror.insert(make_pair("The Dunwich Horror", "H.P. Lovecraft"));
        genreHorror.insert(make_pair("Pet Sematary", "Stephen King"));
        genreHorror.insert(make_pair("The Thing in the Doorstep", "H.P. Lovecraft"));

        cout << endl;
        cout << "How would you like your books sorted?" << endl;
        cout << "1. According to author" << endl;
        cout << "2. According to title" << endl;
        int menuInput1;
        cin >> menuInput1;

        if (menuInput1 == 1) {
            vector<pair<string, string>> sortedAuthors(genreHorror.begin(), genreHorror.end());
            sort(sortedAuthors.begin(), sortedAuthors.end(), [](const pair<string, string>& a, const pair<string, string>& b) {
                return a.second < b.second; 
            });
            cout << "Sorting according to author . . ." << endl;
            for (const auto& pair : sortedAuthors) {
                
                cout << "Author: " << pair.second << ", Title: " << pair.first << endl;
            }
        } else if (menuInput1 == 2) {
            cout << "Sorting according to book title . . ." << endl;
            for (auto it = genreHorror.begin(); it != genreHorror.end(); ++it) {
                
                cout << "Title: " << it->first << ", Author: " << it->second << endl;
            }
        } else {
            cout << "Entry not recognized" << endl;
        }
        cout << endl;
        break;

    case 2:
        genrePoetry.insert(make_pair("Winters of Summers", "Michael Faudet"));
        genrePoetry.insert(make_pair("Lullabies", "Lang Leav"));
        genrePoetry.insert(make_pair("Dirty Pretty Things", "Michael Faudet"));
        genrePoetry.insert(make_pair("On Earth We're Briefly Gorgeous", "Ocean Vuong"));
        genrePoetry.insert(make_pair("No", "Ocean Vuong"));
        genrePoetry.insert(make_pair("Cult of Two", "Michael Faudet"));
        genrePoetry.insert(make_pair("Memories", "Lang Leav"));
        genrePoetry.insert(make_pair("Love and Misadventure", "Lang Leav"));
        genrePoetry.insert(make_pair("Time is a Mother", "Ocean Vuong"));

        cout << endl;
        cout << "How would you like your books sorted?" << endl;
        cout << "1. According to author" << endl;
        cout << "2. According to title" << endl;
        int menuInput2;
        cin >> menuInput2;

        if (menuInput2 == 1) {
            vector<pair<string, string>> sortedAuthors(genrePoetry.begin(), genrePoetry.end());
            sort(sortedAuthors.begin(), sortedAuthors.end(), [](const pair<string, string>& a, const pair<string, string>& b) {
                return a.second < b.second; 
            });
            cout << "Sorting according to author . . ." << endl;
            for (const auto& pair : sortedAuthors) {
                
                cout << "Author: " << pair.second << ", Title: " << pair.first << endl;
            }
        } else if (menuInput2 == 2) {
            cout << "Sorting according to book title . . ." << endl;
            for (auto it = genrePoetry.begin(); it != genrePoetry.end(); ++it) {
                
                cout << "Title: " << it->first << ", Author: " << it->second << endl;
            }
        } else {
            cout << "Entry not recognized" << endl;
        }
        cout << endl;
        break;

    case 3:
        genreFantasy.insert(make_pair("Metro 2033", "Dmitry Glukhovsky"));
        genreFantasy.insert(make_pair("Time of Contempt", "Andrzej Sapkowski"));
        genreFantasy.insert(make_pair("The Murders in the Rue Morgue", "Edgar Allan Poe"));
        genreFantasy.insert(make_pair("Metro 2034", "Dmitry Glukhovsky"));
        genreFantasy.insert(make_pair("Lord of the Rings", "J.R.R. Tolkien"));
        genreFantasy.insert(make_pair("A Song of Ice and Fire", "George R. R. Martin"));
        genreFantasy.insert(make_pair("Ruination", "Anthony Reynolds"));
        genreFantasy.insert(make_pair("The Last Wish", "Andrzej Sapkowski"));

        cout << endl;
        cout << "How would you like your books sorted?" << endl;
        cout << "1. According to author" << endl;
        cout << "2. According to title" << endl;
        int menuInput3;
        cin >> menuInput3;

        if (menuInput3 == 1) {
            vector<pair<string, string>> sortedAuthors(genreFantasy.begin(), genreFantasy.end());
            sort(sortedAuthors.begin(), sortedAuthors.end(), [](const pair<string, string>& a, const pair<string, string>& b) {
                return a.second < b.second; 
            });
            cout << "Sorting according to author . . ." << endl;
            for (const auto& pair : sortedAuthors) {
                
                cout << "Author: " << pair.second << ", Title: " << pair.first << endl;
            }
        } else if (menuInput1 == 2) {
            cout << "Sorting according to book title . . ." << endl;
            for (auto it = genreFantasy.begin(); it != genreFantasy.end(); ++it) {
                
                cout << "Title: " << it->first << ", Author: " << it->second << endl;
            }
        } else {
            cout << "Entry not recognized" << endl;
        }
        cout << endl;
        break;

    case 4:
        // Exiting
        cout << "Exiting program." << endl;
        break;

    default:
        cout << "Entry not recognized" << endl;
        break;
    }
}
