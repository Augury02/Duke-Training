#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <memory>

using namespace std;

enum class Author { EdgarAllanPoe, StephenKing, HPLovecraft, MichaelFaudet, OceanVuong, LangLeav, DmitryGlukhovsky, AndrzejSapkowski, JRRTolkien };
enum class Genre { Horror, Poetry, Fantasy };

// Flyweight class for shared state
class BookFlyweight {
public:
    BookFlyweight(Author author, Genre genre)
        : author(author), genre(genre) {}

    Author getAuthor() const { return author; }
    Genre getGenre() const { return genre; }

private:
    Author author;
    Genre genre;
};

// Flyweight Factory
class BookFlyweightFactory {
public:
    shared_ptr<BookFlyweight> getFlyweight(Author author, Genre genre) {
        string key = to_string(static_cast<int>(author)) + ":" + to_string(static_cast<int>(genre));
        if (flyweights.find(key) == flyweights.end()) {
            flyweights[key] = make_shared<BookFlyweight>(author, genre);
        }
        return flyweights[key];
    }

    // Method to add new author to the flyweight factory
    void addAuthor(Author author) {
        // Check if author already exists
        if (authorMappings.find(static_cast<int>(author)) == authorMappings.end()) {
            authorMappings[static_cast<int>(author)] = true;
        }
    }

    // Method to add new genre to the flyweight factory
    void addGenre(Genre genre) {
        // Check if genre already exists
        if (genreMappings.find(static_cast<int>(genre)) == genreMappings.end()) {
            genreMappings[static_cast<int>(genre)] = true;
        }
    }

private:
    unordered_map<string, shared_ptr<BookFlyweight>> flyweights;
    unordered_map<int, bool> authorMappings;
    unordered_map<int, bool> genreMappings;
};

// Book class
struct Book {
    Book(const string& title, shared_ptr<BookFlyweight> flyweight)
        : title(title), flyweight(flyweight) {}

    string title;
    shared_ptr<BookFlyweight> flyweight;
};

// Display function for books
void displayBooks(const vector<Book*>& books) {
    cout << left << setw(30) << "Title" << setw(20) << "Author" << setw(20) << "Genre" << endl;
    cout << "-----------------------------------------------------------------------------" << endl;
    for (const auto& book : books) {
        cout << left << setw(30) << book->title;
        switch (book->flyweight->getAuthor()) {
            case Author::EdgarAllanPoe: cout << setw(20) << "Edgar Allan Poe"; break;
            case Author::StephenKing: cout << setw(20) << "Stephen King"; break;
            case Author::HPLovecraft: cout << setw(20) << "H.P. Lovecraft"; break;
            case Author::MichaelFaudet: cout << setw(20) << "Michael Faudet"; break;
            case Author::OceanVuong: cout << setw(20) << "Ocean Vuong"; break;
            case Author::LangLeav: cout << setw(20) << "Lang Leav"; break;
            case Author::DmitryGlukhovsky: cout << setw(20) << "Dmitry Glukhovsky"; break;
            case Author::AndrzejSapkowski: cout << setw(20) << "Andrzej Sapkowski"; break;
            case Author::JRRTolkien: cout << setw(20) << "J.R.R. Tolkien"; break;
            default: cout << setw(20) << "Unknown Author"; break;  // Handle unknown authors
        }
        switch (book->flyweight->getGenre()) {
            case Genre::Horror: cout << setw(20) << "Horror"; break;
            case Genre::Poetry: cout << setw(20) << "Poetry"; break;
            case Genre::Fantasy: cout << setw(20) << "Fantasy"; break;
            default: cout << setw(20) << "Unknown Genre"; break;  // Handle unknown genres
        }
        cout << endl;
    }
}

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
        return item->flyweight->getAuthor() == author;
    }
};

// Genre specification
struct GenreSpecification : Specification<Book> {
    Genre genre;

    explicit GenreSpecification(Genre genre) : genre(genre) {}

    bool is_satisfied(Book* item) override {
        return item->flyweight->getGenre() == genre;
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

// BetterFilter implementation
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
            if (item->flyweight->getAuthor() == author)
                result.push_back(item);
        return result;
    }

    vector<Book*> filter_by_genre(vector<Book*> items, Genre genre) {
        vector<Book*> result;
        for (auto& item : items)
            if (item->flyweight->getGenre() == genre)
                result.push_back(item);
        return result;
    }

    vector<Book*> filter_by_genre_and_author(vector<Book*> items, Genre genre, Author author) {
        vector<Book*> result;
        for (auto& item : items)
            if (item->flyweight->getGenre() == genre && item->flyweight->getAuthor() == author)
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

// LibraryFacade class
class LibraryFacade {
    vector<Book*> books;
    BetterFilter betterFilter;
    LegacyBookFilter legacyFilter;
    LegacyFilterAdapter legacyAdapter;

public:
    LibraryFacade(vector<Book*>& books)
        : books(books), legacyAdapter(legacyFilter) {}

    vector<Book*> filterByAuthor(Author author) {
        AuthorSpecification authorSpec(author);
        return betterFilter.filter(books, authorSpec);
    }

    vector<Book*> filterByGenre(Genre genre) {
        GenreSpecification genreSpec(genre);
        return betterFilter.filter(books, genreSpec);
    }

    vector<Book*> filterByGenreAndAuthor(Genre genre, Author author) {
        AuthorSpecification authorSpec(author);
        GenreSpecification genreSpec(genre);
        AndSpecification<Book> andSpec(authorSpec, genreSpec);
        return betterFilter.filter(books, andSpec);
    }

    vector<Book*> sortBooksByTitle() {
        vector<Book*> sortedBooks = books;
        sort(sortedBooks.begin(), sortedBooks.end(), [](Book* a, Book* b) {
            return a->title < b->title;
        });
        return sortedBooks;
    }

    vector<Book*> getAllBooks() const {
        return books;
    }
    
    // Method to add new book with author and genre addition
    void addBook(const string& title, Author author, Genre genre, BookFlyweightFactory& factory) {
        factory.addAuthor(author);
        factory.addGenre(genre);
        auto flyweight = factory.getFlyweight(author, genre);
        books.push_back(new Book(title, flyweight));
    }

    // Method to remove a book
    bool removeBook(const string& title) {
        auto it = find_if(books.begin(), books.end(), [&](Book* book) {
            return book->title == title;
        });

        if (it != books.end()) {
            books.erase(it);
            return true;
        }

        return false;
    }
};

int showMainMenu() {
    int choice;
    cout << "===== MAIN MENU =====" << endl;
    cout << "1. View Library" << endl;
    cout << "2. Add Books" << endl;
    cout << "3. Add Authors and Genres" << endl;
    cout << "4. Remove Books" << endl;  // Option to remove books
    cout << "5. Exit" << endl;
    cout << "Enter your choice: ";
    cin >> choice;
    return choice;
}

// Function to show menu for viewing library
int showLibraryMenu() {
    int choice;
    cout << "===== VIEW LIBRARY MENU =====" << endl;
    cout << "1. Filter by Author" << endl;
    cout << "2. Filter by Genre" << endl;
    cout << "3. Filter by Genre and Author" << endl;
    cout << "4. Sort Books Alphabetically by Title" << endl;
    cout << "5. Back to Main Menu" << endl;
    cout << "Enter your choice: ";
    cin >> choice;
    return choice;
}

// Function to select author
int authorSelection() {
    int choice;
    cout << " " << endl;
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
    cout << " " << endl;
    cout << "Select a genre:" << endl;
    cout << "1. Horror" << endl;
    cout << "2. Poetry" << endl;
    cout << "3. Fantasy" << endl;
    cout << "4. Back to main menu" << endl;
    cout << "Enter your choice: ";
    cin >> choice;
    return choice;
}

// Function to add new authors
void addNewAuthor(BookFlyweightFactory& factory) {
    int choice;
    cout << "Select an author to add:" << endl;
    cout << "1. Edgar Allan Poe" << endl;
    cout << "2. Stephen King" << endl;
    // Add other authors as needed

    cin >> choice;
    factory.addAuthor(static_cast<Author>(choice - 1));
}

// Function to add new genres
void addNewGenre(BookFlyweightFactory& factory) {
    int choice;
    cout << "Select a genre to add:" << endl;
    cout << "1. Horror" << endl;
    cout << "2. Poetry" << endl;
    // Add other genres as needed

    cin >> choice;
    factory.addGenre(static_cast<Genre>(choice - 1));
}

void removeBookFromLibrary(LibraryFacade& library) {
    string titleToRemove;
    cout << "Enter the title of the book to remove: ";
    cin.ignore();  // Ignore newline character in input buffer
    getline(cin, titleToRemove);

    if (library.removeBook(titleToRemove)) {
        cout << "Book '" << titleToRemove << "' removed successfully!" << endl;
    } else {
        cout << "Book '" << titleToRemove << "' not found in the library." << endl;
    }
}

int main() {
    BookFlyweightFactory flyweightFactory;
    vector<Book> allBooks{
    Book("Black Cat", flyweightFactory.getFlyweight(Author::EdgarAllanPoe, Genre::Horror)),
    Book("The Murders in the Rue Morgue", flyweightFactory.getFlyweight(Author::EdgarAllanPoe, Genre::Horror)),
    Book("The Oval Portrait", flyweightFactory.getFlyweight(Author::EdgarAllanPoe, Genre::Horror)),
    Book("Salem's Lot", flyweightFactory.getFlyweight(Author::StephenKing, Genre::Horror)),
    Book("Pet Sematary", flyweightFactory.getFlyweight(Author::StephenKing, Genre::Horror)),
    Book("The Dunwich Horror", flyweightFactory.getFlyweight(Author::HPLovecraft, Genre::Horror)),
    Book("The Thing in the Doorstep", flyweightFactory.getFlyweight(Author::HPLovecraft, Genre::Horror)),
    Book("Color out of space", flyweightFactory.getFlyweight(Author::HPLovecraft, Genre::Horror)),
    Book("Winters of Summers", flyweightFactory.getFlyweight(Author::MichaelFaudet, Genre::Poetry)),
    Book("No", flyweightFactory.getFlyweight(Author::OceanVuong, Genre::Poetry)),
    Book("On Earth We're Briefly...", flyweightFactory.getFlyweight(Author::OceanVuong, Genre::Poetry)),
    Book("Memories", flyweightFactory.getFlyweight(Author::LangLeav, Genre::Poetry)),
    Book("Dirty Pretty Things", flyweightFactory.getFlyweight(Author::MichaelFaudet, Genre::Poetry)),
    Book("Love and Misadventure", flyweightFactory.getFlyweight(Author::LangLeav, Genre::Poetry)),
    Book("Lullabies", flyweightFactory.getFlyweight(Author::LangLeav, Genre::Poetry)),
    Book("Cult of Two", flyweightFactory.getFlyweight(Author::MichaelFaudet, Genre::Poetry)),
    Book("Time is a Mother", flyweightFactory.getFlyweight(Author::OceanVuong, Genre::Poetry)),
    Book("Metro 2033", flyweightFactory.getFlyweight(Author::DmitryGlukhovsky, Genre::Fantasy)),
    Book("Time of Contempt", flyweightFactory.getFlyweight(Author::AndrzejSapkowski, Genre::Fantasy)),
    Book("Lord of the Rings", flyweightFactory.getFlyweight(Author::JRRTolkien, Genre::Fantasy))
    };
    // Define some initial books using the flyweight factory
    
    // Add more books as needed...

    vector<Book*> books;
    for (auto& book : allBooks) {
        books.push_back(new Book(book));
    }

    LibraryFacade library(books);

    int mainChoice;
    do {
        mainChoice = showMainMenu();

        switch (mainChoice) {
            case 1: {
                int libraryChoice;
                do {
                    libraryChoice = showLibraryMenu();

                    switch (libraryChoice) {
                        case 1: {
                            int authorChoice = authorSelection();
                            if (authorChoice >= 1 && authorChoice <= 9) {
                                auto filteredBooks = library.filterByAuthor(static_cast<Author>(authorChoice - 1));
                                cout << " " << endl;
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
                                auto filteredBooks = library.filterByGenre(static_cast<Genre>(genreChoice - 1));
                                cout << " " << endl;
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
                                    auto filteredBooks = library.filterByGenreAndAuthor(static_cast<Genre>(genreChoice - 1), static_cast<Author>(authorChoice - 1));
                                    cout << " " << endl;
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
                            auto sortedBooks = library.sortBooksByTitle();
                            cout << " " << endl;
                            cout << "Books sorted alphabetically by title:" << endl;
                            displayBooks(sortedBooks);
                            break;
                        }
                        case 5: {
                            cout << "Returning to main menu..." << endl;
                            break;
                        }
                        default:
                            cout << "Invalid choice. Please try again." << endl;
                            break;
                    }

                    cout << endl;

                } while (libraryChoice != 5);

                break;
            }
            case 2: {   //ADD BOOK
                string title;
                int authorChoice, genreChoice;

                cout << "Enter the title of the book: ";
                cin.ignore(); // Ignore newline character in input buffer
                getline(cin, title);

                authorChoice = authorSelection();
                genreChoice = genreSelection();

                if (authorChoice >= 1 && authorChoice <= 9 && genreChoice >= 1 && genreChoice <= 3) {
                    library.addBook(title, static_cast<Author>(authorChoice - 1), static_cast<Genre>(genreChoice - 1), flyweightFactory);
                    cout << "Book added successfully!" << endl;
                } else {
                    cout << "Invalid author or genre selection. Book not added." << endl;
                }

                break;
            }
            case 3: {   // ADD Authors and Genres
                int addChoice;
                cout << "===== ADD AUTHORS AND GENRES MENU =====" << endl;
                cout << "1. Add New Author" << endl;
                cout << "2. Add New Genre" << endl;
                cout << "3. Back to Main Menu" << endl;
                cout << "Enter your choice: ";
                cin >> addChoice;

                switch (addChoice) {
                    case 1:
                        addNewAuthor(flyweightFactory);
                        break;
                    case 2:
                        addNewGenre(flyweightFactory);
                        break;
                    case 3:
                        cout << "Returning to main menu..." << endl;
                        break;
                    default:
                        cout << "Invalid choice. Please try again." << endl;
                        break;
                }
                break; // Add this break statement
            }
            case 4: {
                // Remove Books
                removeBookFromLibrary(library);
                break;
            }
            case 5:
                cout << "Exiting the program..." << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
                break;
        }

        cout << endl;

    } while (mainChoice != 5);

    return 0;
}
