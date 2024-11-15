#include <iostream>
#include <string>
#include <vector>
#include <memory> // For smart pointers

using namespace std;

// Abstract Base Class
class LibraryItem {
protected:
    string title;
    string author;
    string dueDate;

public:
    // Virtual destructor for proper cleanup
    virtual ~LibraryItem() {}

    // Pure virtual functions
    virtual void checkOut() = 0;
    virtual void returnItem() = 0;
    virtual void displayDetails() const = 0;

    // Encapsulation with getters and setters
    string getTitle() const { return title; }
    string getAuthor() const { return author; }
    string getDueDate() const { return dueDate; }

    void setTitle(const string& newTitle) { title = newTitle; }
    void setAuthor(const string& newAuthor) { author = newAuthor; }
    void setDueDate(const string& newDueDate) { dueDate = newDueDate; }
};

// Derived Class: Book
class Book : public LibraryItem {
private:
    string isbn;

public:
    Book(const string& title, const string& author, const string& isbn)
    {
        setTitle(title);
        setAuthor(author);
        this->isbn = isbn;
    }

    void checkOut() override {
        cout << "Book \"" << title << "\" has been checked out.\n";
        dueDate = "2024-12-01"; // Example due date
    }

    void returnItem() override {
        cout << "Book \"" << title << "\" has been returned.\n";
        dueDate = "";
    }

    void displayDetails() const override {
        cout << "Book Title: " << title << "\nAuthor: " << author << "\nISBN: " << isbn;
        if (!dueDate.empty())
            cout << "\nDue Date: " << dueDate;
        cout << "\n";
    }
};

// Derived Class: DVD
class DVD : public LibraryItem {
private:
    int duration; // Duration in minutes

public:
    DVD(const string& title, const string& author, int duration)
    {
        setTitle(title);
        setAuthor(author);
        this->duration = duration;
    }

    void checkOut() override {
        cout << "DVD \"" << title << "\" has been checked out.\n";
        dueDate = "2024-12-10"; // Example due date
    }

    void returnItem() override {
        cout << "DVD \"" << title << "\" has been returned.\n";
        dueDate = "";
    }

    void displayDetails() const override {
        cout << "DVD Title: " << title << "\nDirector: " << author
             << "\nDuration: " << duration << " minutes";
        if (!dueDate.empty())
            cout << "\nDue Date: " << dueDate;
        cout << "\n";
    }
};

// Derived Class: Magazine
class Magazine : public LibraryItem {
private:
    int issueNumber;

public:
    Magazine(const string& title, const string& author, int issueNumber)
    {
        setTitle(title);
        setAuthor(author);
        this->issueNumber = issueNumber;
    }

    void checkOut() override {
        cout << "Magazine \"" << title << "\" has been checked out.\n";
        dueDate = "2024-12-15"; // Example due date
    }

    void returnItem() override {
        cout << "Magazine \"" << title << "\" has been returned.\n";
        dueDate = "";
    }

    void displayDetails() const override {
        cout << "Magazine Title: " << title << "\nAuthor: " << author
             << "\nIssue Number: " << issueNumber;
        if (!dueDate.empty())
            cout << "\nDue Date: " << dueDate;
        cout << "\n";
    }
};

// Menu-driven interface
void displayMenu() {
    cout << "\nLibrary Management System\n";
    cout << "1. Add Item\n";
    cout << "2. Display Items\n";
    cout << "3. Check Out Item\n";
    cout << "4. Return Item\n";
    cout << "5. Exit\n";
    cout << "Enter your choice: ";
}

int main() {
    vector<shared_ptr<LibraryItem>> libraryItems; // Using smart pointers for automatic cleanup
    int choice;

    while (true) {
        displayMenu();
        cin >> choice;

        if (choice == 1) {
            int type;
            cout << "Select type: 1. Book  2. DVD  3. Magazine: ";
            cin >> type;

            string title, author;
            cout << "Enter title: ";
            cin.ignore(); // To consume the newline character
            getline(cin, title);
            cout << "Enter author: ";
            getline(cin, author);

            if (type == 1) {
                string isbn;
                cout << "Enter ISBN: ";
                cin >> isbn;
                libraryItems.push_back(make_shared<Book>(title, author, isbn));
            } else if (type == 2) {
                int duration;
                cout << "Enter duration (minutes): ";
                cin >> duration;
                libraryItems.push_back(make_shared<DVD>(title, author, duration));
            } else if (type == 3) {
                int issueNumber;
                cout << "Enter issue number: ";
                cin >> issueNumber;
                libraryItems.push_back(make_shared<Magazine>(title, author, issueNumber));
            }
        } else if (choice == 2) {
            for (const auto& item : libraryItems)
                item->displayDetails();
        } else if (choice == 3) {
            string title;
            cout << "Enter title to check out: ";
            cin.ignore();
            getline(cin, title);
            for (const auto& item : libraryItems) {
                if (item->getTitle() == title) {
                    item->checkOut();
                    break;
                }
            }
        } else if (choice == 4) {
            string title;
            cout << "Enter title to return: ";
            cin.ignore();
            getline(cin, title);
            for (const auto& item : libraryItems) {
                if (item->getTitle() == title) {
                    item->returnItem();
                    break;
                }
            }
        } else if (choice == 5) {
            cout << "Exiting...\n";
            break;
        } else {
            cout << "Invalid choice! Try again.\n";
        }
    }

    return 0;
}
