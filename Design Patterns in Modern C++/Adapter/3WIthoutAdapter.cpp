#include <iostream>
#include <map>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;

enum class Genre { Horror, Fantasy, Poetry };
enum class Author { HPLovecraft, EdgarAllanPoe, StephenKing,
                    MichaelFaudet, LangLeav, OceanVuong,
                    DmitryGlukhovsky, AndrzejSapkowski, JRRTolkien };

struct Book {
    string title;
    Genre genre;
    Author author;
};

struct BookFilter {
    typedef vector<Book*> Items;

    Items by_genre(Items items, const Genre genre) {
        Items result;
        for (auto& i : items)
            if (i->genre == genre)
                result.push_back(i);
        return result;
    }

    Items by_author(Items items, const Author author) {
        Items result;
        for (auto& i : items)
            if (i->author == author)
                result.push_back(i);
        return result;
    }

    Items by_genre_and_author(Items items, const Genre genre, const Author author) {
        Items result;
        for (auto& i : items)
            if (i->genre == genre && i->author == author)
                result.push_back(i);
        return result;
    }
};

template <typename T> struct Specification {
    virtual ~Specification() = default;
    virtual bool is_satisfied(T* item) const = 0;
};

template <typename T> struct AndSpecification;

template <typename T> AndSpecification<T> operator&&
(const Specification<T>& first, const Specification<T>& second) {
    return { first, second };
}

template <typename T> struct Filter {
    virtual vector<T*> filter(vector<T*> items,
                              Specification<T>& spec) = 0;
};

struct BetterFilter : Filter<Book> {
    vector<Book*> filter(vector<Book*> items,
                         Specification<Book> &spec) override {
        vector<Book*> result;
        for (auto& p : items)
            if (spec.is_satisfied(p))
                result.push_back(p);
        return result;
    }
};

struct GenreSpecification : Specification<Book> {
    Genre genre;

    GenreSpecification(Genre genre) : genre(genre) {}

    bool is_satisfied(Book *item) const override {
        return item->genre == genre;
    }
};

struct AuthorSpecification : Specification<Book> {
    Author author;
    explicit AuthorSpecification(const Author author)
        : author{ author }
    {
    }
    bool is_satisfied(Book* item) const override {
        return item->author == author;
    }
};

template <typename T> struct AndSpecification : Specification<T> {
    const Specification<T>& first;
    const Specification<T>& second;

    AndSpecification(const Specification<T>& first, const Specification<T>& second)
        : first(first), second(second) {}

    bool is_satisfied(T *item) const override {
        return first.is_satisfied(item) && second.is_satisfied(item);
    }
};

int showMenu() {
    cout << "===== BETTER LIBRARY =====" << endl;
    cout << "-combines library locator, and library sorter features!-" << endl;
    cout << "Select an option (1-5):" << endl;
    cout << "1. Locate books by Author" << endl;
    cout << "2. Locate books by Genre" << endl;
    cout << "3. Locate books by both Author and Genre" << endl;
    cout << "4. Display books in alphabetical order" << endl;
    cout << "5. Exit" << endl;
    cout << "Input your selection: ";
    int menuInput;
    cin >> menuInput;
    return menuInput;
}

int authorSelection() {
    cout << " " << endl;
    cout << "List of authors:" << endl;
    cout << "1. H.P. Lovecraft" << endl;
    cout << "2. Edgar Allan Poe" << endl;
    cout << "3. Stephen King" << endl;
    cout << "4. Michael Faudet" << endl;
    cout << "5. Lang Leav" << endl;
    cout << "6. Ocean Vuong" << endl;
    cout << "7. Dmitry Glukhovsky" << endl;
    cout << "8. Andrzej Sapkowski" << endl;
    cout << "9. J.R.R. Tolkien" << endl;
    cout << "10. Return to Main Menu" << endl;
    cout << "Locate books according to which author: ";
    int authorLocatorInput;
    cin >> authorLocatorInput;
    return authorLocatorInput;
}

int genreSelection() {
    cout << " " << endl;
    cout << "List of Genres:" << endl;
    cout << "1. Horror" << endl;
    cout << "2. Poetry" << endl;
    cout << "3. Fantasy" << endl;
    cout << "4. Return to Main Menu" << endl;
    cout << "Locate books according to which genre: ";
    int genreLocatorInput;
    cin >> genreLocatorInput;
    return genreLocatorInput;
}

void displayBooks(const vector<Book*>& books) {
    for (auto& book : books)
        cout << book->title << endl;
    cout << " " << endl;
}

int main() {
    //Horror
    Book book1{ "Black Cat", Genre::Horror, Author::EdgarAllanPoe };
    Book book2{ "The Murders in the Rue Morgue", Genre::Horror, Author::EdgarAllanPoe };
    Book book3{ "The Oval Portrait", Genre::Horror, Author::EdgarAllanPoe };
    Book book4{ "Salem's Lot", Genre::Horror, Author::StephenKing };
    Book book5{ "Pet Sematary", Genre::Horror, Author::StephenKing };
    Book book6{ "The Dunwich Horror", Genre::Horror, Author::HPLovecraft };
    Book book7{ "The Thing in the Doorstep", Genre::Horror, Author::HPLovecraft };
    Book book8{ "Color out of space", Genre::Horror, Author::HPLovecraft };
    //POETRY
    Book book9{ "Winters of Summers", Genre::Poetry, Author::MichaelFaudet };
    Book book10{ "No", Genre::Poetry, Author::OceanVuong };
    Book book11{ "On Earth We're Briefly Gorgeous", Genre::Poetry, Author::OceanVuong };
    Book book12{ "Memories", Genre::Poetry, Author::LangLeav };
    Book book13{ "Dirty Pretty Things", Genre::Poetry, Author::MichaelFaudet };
    Book book14{ "Love and Misadventure", Genre::Poetry, Author::LangLeav };
    Book book15{ "Lullabies", Genre::Poetry, Author::LangLeav };
    Book book16{ "Cult of Two", Genre::Poetry, Author::MichaelFaudet };
    Book book17{ "Time is a Mother", Genre::Poetry, Author::OceanVuong };
    //Fantasy
    Book book18{ "Metro 2033", Genre::Fantasy, Author::DmitryGlukhovsky };
    Book book19{ "Time of Contempt", Genre::Fantasy, Author::AndrzejSapkowski };
    Book book20{ "Lord of the Rings", Genre::Fantasy, Author::JRRTolkien };

    const vector<Book*> all{ &book1, &book2, &book3, &book4, &book5,
                             &book6, &book7, &book8, &book9, &book10,
                             &book11, &book12, &book13, &book14, &book15,
                             &book16, &book17, &book18, &book19, &book20 };

    int menuInput;

    do {
        menuInput = showMenu();
        int authorLocatorInput;
        int genreLocatorInput;

        if (menuInput == 1) {
            authorLocatorInput = authorSelection();
            if (authorLocatorInput >= 1 && authorLocatorInput <= 9) {
                BetterFilter bf;
                AuthorSpecification authorSpec(static_cast<Author>(authorLocatorInput - 1));
                auto filteredBooks = bf.filter(all, authorSpec);
                cout << " " << endl;
                cout << "Books written by the author include: " << endl;
                displayBooks(filteredBooks);
            } else if (authorLocatorInput == 10) {
                cout << "Returning to Main menu. . ." << endl;
                cout << " " << endl;
                continue;
            }
        } else if (menuInput == 2) {
            genreLocatorInput = genreSelection();
            if (genreLocatorInput >= 1 && genreLocatorInput <= 3) {
                BetterFilter bf;
                GenreSpecification genreSpec(static_cast<Genre>(genreLocatorInput - 1));
                auto filteredBooks = bf.filter(all, genreSpec);
                cout << " " << endl;
                cout << "Books under the genre include: " << endl;
                displayBooks(filteredBooks);
            } else if (genreLocatorInput == 4) {
                cout << "Returning to Main menu. . ." << endl;
                cout << " " << endl;
                continue;
            }
        } else if (menuInput == 3) {
            cout << "Enter the author (1-9)" << endl;
            authorLocatorInput = authorSelection();
            cout << " " << endl;
            if (authorLocatorInput >= 1 && authorLocatorInput <= 9) {
                cout << "Enter the genre (1-3)" << endl;
                genreLocatorInput = genreSelection();
                if (genreLocatorInput >= 1 && genreLocatorInput <= 3) {
                    BetterFilter bf;
                    GenreSpecification genreSpec(static_cast<Genre>(genreLocatorInput - 1));
                    AuthorSpecification authorSpec(static_cast<Author>(authorLocatorInput - 1));
                    AndSpecification<Book> andSpec(genreSpec, authorSpec);
                    auto filteredBooks = bf.filter(all, andSpec);
                    cout << " " << endl;
                    cout << "Books written by the author under this genre include: " << endl;
                    displayBooks(filteredBooks);
                }
            } else if (authorLocatorInput == 10) {
                cout << "Returning to Main menu. . ." << endl;
                cout << " " << endl;
                continue;
            }
        } else if (menuInput == 4) {
            cout << "Books in alphabetical order: " << endl;
            cout << endl;
            vector<Book*> sortedBooks = all;
            sort(sortedBooks.begin(), sortedBooks.end(), [](Book* a, Book* b) {
                return a->title < b->title;
            });
            displayBooks(sortedBooks);
        } else if (menuInput == 5) {
            cout << "Exiting program. . ." << endl;
            return 0;
        }
    } while (menuInput != 5);

    return 0;
}
