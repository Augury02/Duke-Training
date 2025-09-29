#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

enum class Author { EdgarAllanPoe, StephenKing, HPLovecraft, MichaelFaudet, OceanVuong, LangLeav, DmitryGlukhovsky, AndrzejSapkowski, JRRTolkien };
enum class Genre { Horror, Poetry, Fantasy };

// Book structure
struct Book {
    string title;
    Genre genre;
    Author author;
};

// Specification interface
template<typename T>
struct Specification {
    virtual bool is_satisfied(T* item) = 0;
};

// Author specification
struct AuthorSpecification : Specification<Book> {
    Author author;

    explicit AuthorSpecification(Author author) : author(author) {}

    bool is_satisfied(Book* item) override {
        return item->author == author;
    }
};

// Genre specification
struct GenreSpecification : Specification<Book> {
    Genre genre;

    explicit GenreSpecification(Genre genre) : genre(genre) {}

    bool is_satisfied(Book* item) override {
        return item->genre == genre;
    }
};

// AND specification
template<typename T>
struct AndSpecification : Specification<T> {
    Specification<T>& first;
    Specification<T>& second;

    AndSpecification(Specification<T>& first, Specification<T>& second) : first(first), second(second) {}

    bool is_satisfied(T* item) override {
        return first.is_satisfied(item) && second.is_satisfied(item);
    }
};

// Filter interface
template<typename T>
struct Filter {
    virtual vector<T*> filter(vector<T*> items, Specification<T>& spec) = 0;
};

// BetterFilter implementation; Check Builder topic
struct BetterFilter : Filter<Book> {
    vector<Book*> filter(vector<Book*> items, Specification<Book>& spec) override {
        vector<Book*> result;
        for (auto& item : items) {
            if (spec.is_satisfied(item)) {
                result.push_back(item);
            }
        }
        return result;
    }
};

// LegacyBookFilter implementation 
struct LegacyBookFilter {
    vector<Book*> filter_by_author(vector<Book*> items, Author author) {
        vector<Book*> result;
        for (auto& item : items)
            if (item->author == author)
                result.push_back(item);
        return result;
    }

    vector<Book*> filter_by_genre(vector<Book*> items, Genre genre) {
        vector<Book*> result;
        for (auto& item : items)
            if (item->genre == genre)
                result.push_back(item);
        return result;
    }

    vector<Book*> filter_by_genre_and_author(vector<Book*> items, Genre genre, Author author) {
        vector<Book*> result;
        for (auto& item : items)
            if (item->genre == genre && item->author == author)
                result.push_back(item);
        return result;
    }
};

// Adapter for LegacyBookFilter to work with Filter<Book> interface
struct LegacyFilterAdapter : Filter<Book> {
    LegacyBookFilter& legacyFilter;

    explicit LegacyFilterAdapter(LegacyBookFilter& legacyFilter)
        : legacyFilter(legacyFilter) {}

    vector<Book*> filter(vector<Book*> items, Specification<Book>& spec) override {
        if (auto* authorSpec = dynamic_cast<AuthorSpecification*>(&spec)) {
            return legacyFilter.filter_by_author(items, authorSpec->author);
        } else if (auto* genreSpec = dynamic_cast<GenreSpecification*>(&spec)) {
            return legacyFilter.filter_by_genre(items, genreSpec->genre);
        } else if (auto* andSpec = dynamic_cast<AndSpecification<Book>*>(&spec)) {
            if (auto* genreSpec = dynamic_cast<GenreSpecification*>(&andSpec->first)) {
                if (auto* authorSpec = dynamic_cast<AuthorSpecification*>(&andSpec->second)) {
                    return legacyFilter.filter_by_genre_and_author(items, genreSpec->genre, authorSpec->author);
                }
            }
        }
        return {};
    }
};

// Display function for books
void displayBooks(const vector<Book*>& books) {
    for (const auto& book : books) {
        cout << "Title: " << book->title << ", Author: ";
        switch (book->author) {
            case Author::EdgarAllanPoe: cout << "Edgar Allan Poe"; break;
            case Author::StephenKing: cout << "Stephen King"; break;
            case Author::HPLovecraft: cout << "H.P. Lovecraft"; break;
            case Author::MichaelFaudet: cout << "Michael Faudet"; break;
            case Author::OceanVuong: cout << "Ocean Vuong"; break;
            case Author::LangLeav: cout << "Lang Leav"; break;
            case Author::DmitryGlukhovsky: cout << "Dmitry Glukhovsky"; break;
            case Author::AndrzejSapkowski: cout << "Andrzej Sapkowski"; break;
            case Author::JRRTolkien: cout << "J.R.R. Tolkien"; break;
        }
        cout << ", Genre: ";
        switch (book->genre) {
            case Genre::Horror: cout << "Horror"; break;
            case Genre::Poetry: cout << "Poetry"; break;
            case Genre::Fantasy: cout << "Fantasy"; break;
        }
        cout << endl;
    }
}

// Function to show menu
int showMenu() {
    int choice;
    cout << "===== WELCOME TO THE BETTER LIBRARY MENU =====" << endl;
    cout << "-this time, with adapters!-" << endl;
    cout << "1. Filter by Author" << endl;
    cout << "2. Filter by Genre" << endl;
    cout << "3. Filter by Genre and Author" << endl;
    cout << "4. Sort Books Alphabetically by Title" << endl;
    cout << "5. Exit" << endl;
    cout << "Enter your choice: ";
    cin >> choice;
    return choice;
}

// Function to select author
int authorSelection() {
    int choice;
    cout << "Select an author:" << endl;
    cout << "1. Edgar Allan Poe" << endl;
    cout << "2. Stephen King" << endl;
    cout << "3. H.P. Lovecraft" << endl;
    cout << "4. Michael Faudet" << endl;
    cout << "5. Ocean Vuong" << endl;
    cout << "6. Lang Leav" << endl;
    cout << "7. Dmitry Glukhovsky" << endl;
    cout << "8. Andrzej Sapkowski" << endl;
    cout << "9. J.R.R. Tolkien" << endl;
    cout << "10. Back to main menu" << endl;
    cout << "Enter your choice: ";
    cin >> choice;
    return choice;
}

// Function to select genre
int genreSelection() {
    int choice;
    cout << "Select a genre:" << endl;
    cout << "1. Horror" << endl;
    cout << "2. Poetry" << endl;
    cout << "3. Fantasy" << endl;
    cout << "4. Back to main menu" << endl;
    cout << "Enter your choice: ";
    cin >> choice;
    return choice;
}

int main() {
    // Create sample books
    Book book1{ "Black Cat", Genre::Horror, Author::EdgarAllanPoe };
    Book book2{ "The Murders in the Rue Morgue", Genre::Horror, Author::EdgarAllanPoe };
    Book book3{ "The Oval Portrait", Genre::Horror, Author::EdgarAllanPoe };
    Book book4{ "Salem's Lot", Genre::Horror, Author::StephenKing };
    Book book5{ "Pet Sematary", Genre::Horror, Author::StephenKing };
    Book book6{ "The Dunwich Horror", Genre::Horror, Author::HPLovecraft };
    Book book7{ "The Thing in the Doorstep", Genre::Horror, Author::HPLovecraft };
    Book book8{ "Color out of space", Genre::Horror, Author::HPLovecraft };
    Book book9{ "Winters of Summers", Genre::Poetry, Author::MichaelFaudet };
    Book book10{ "No", Genre::Poetry, Author::OceanVuong };
    Book book11{ "On Earth We're Briefly Gorgeous", Genre::Poetry, Author::OceanVuong };
    Book book12{ "Memories", Genre::Poetry, Author::LangLeav };
    Book book13{ "Dirty Pretty Things", Genre::Poetry, Author::MichaelFaudet };
    Book book14{ "Love and Misadventure", Genre::Poetry, Author::LangLeav };
    Book book15{ "Lullabies", Genre::Poetry, Author::LangLeav };
    Book book16{ "Cult of Two", Genre::Poetry, Author::MichaelFaudet };
    Book book17{ "Time is a Mother", Genre::Poetry, Author::OceanVuong };
    Book book18{ "Metro 2033", Genre::Fantasy, Author::DmitryGlukhovsky };
    Book book19{ "Time of Contempt", Genre::Fantasy, Author::AndrzejSapkowski };
    Book book20{ "Lord of the Rings", Genre::Fantasy, Author::JRRTolkien };

    // Create a vector of all books
    vector<Book*> allBooks{ &book1, &book2, &book3, &book4, &book5,
                            &book6, &book7, &book8, &book9, &book10,
                            &book11, &book12, &book13, &book14, &book15,
                            &book16, &book17, &book18, &book19, &book20 };

    int choice;
    BetterFilter betterFilter;
    LegacyBookFilter legacyFilter;
    LegacyFilterAdapter legacyAdapter(legacyFilter);

    do {
        choice = showMenu();

        switch (choice) {
            case 1: {
                int authorChoice = authorSelection();
                if (authorChoice >= 1 && authorChoice <= 9) {
                    AuthorSpecification authorSpec(static_cast<Author>(authorChoice - 1));
                    auto filteredBooks = betterFilter.filter(allBooks, authorSpec);
                    cout << "Books written by the author include:" << endl;
                    displayBooks(filteredBooks);
                } else if (authorChoice == 10) {
                    cout << "Returning to main menu..." << endl;
                } else {
                    cout << "Invalid choice. Please try again." << endl;
                }
                break;
            }
            case 2: {
                int genreChoice = genreSelection();
                if (genreChoice >= 1 && genreChoice <= 3) {
                    GenreSpecification genreSpec(static_cast<Genre>(genreChoice - 1));
                    auto filteredBooks = betterFilter.filter(allBooks, genreSpec);
                    cout << "Books under the genre include:" << endl;
                    displayBooks(filteredBooks);
                } else if (genreChoice == 4) {
                    cout << "Returning to main menu..." << endl;
                } else {
                    cout << "Invalid choice. Please try again." << endl;
                }
                break;
            }
            case 3: {
                int authorChoice = authorSelection();
                if (authorChoice >= 1 && authorChoice <= 9) {
                    int genreChoice = genreSelection();
                    if (genreChoice >= 1 && genreChoice <= 3) {
                        AuthorSpecification authorSpec(static_cast<Author>(authorChoice - 1));
                        GenreSpecification genreSpec(static_cast<Genre>(genreChoice - 1));
                        AndSpecification<Book> andSpec(authorSpec, genreSpec);
                        auto filteredBooks = betterFilter.filter(allBooks, andSpec);
                        cout << "Books written by the author under this genre include:" << endl;
                        displayBooks(filteredBooks);
                    } else if (genreChoice == 4) {
                        cout << "Returning to main menu..." << endl;
                    } else {
                        cout << "Invalid choice. Please try again." << endl;
                    }
                } else if (authorChoice == 10) {
                    cout << "Returning to main menu..." << endl;
                } else {
                    cout << "Invalid choice. Please try again." << endl;
                }
                break;
            }
            case 4: {
                vector<Book*> sortedBooks = allBooks;
                sort(sortedBooks.begin(), sortedBooks.end(), [](Book* a, Book* b) {
                    return a->title < b->title;
                });
                cout << "Books sorted alphabetically by title:" << endl;
                displayBooks(sortedBooks);
                break;
            }
            case 5: {
                cout << "Exiting the program..." << endl;
                break;
            }
            default:
                cout << "Invalid choice. Please try again." << endl;
                break;
        }

        cout << endl;

    } while (choice != 5);

    return 0;
}
