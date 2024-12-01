#include "BTree.h"


// Function to display the main menu
void displayMenu() {
    cout << "\nLibrary Catalog Management System\n";
    cout << "1. Display Catalog\n";
    cout << "2. Search for a Book\n";
    cout << "3. Insert a Book\n";
    cout << "4. Delete a Book\n";
    cout << "5. Modify book information\n";
    cout << "6. Exit\n";
    cout << "Enter your choice: ";
}

int main() {
    BTree<Book, 100> bookTree;

    // Insert books into the tree
    int choice;
    do {
        displayMenu();
        cin >> choice;
        cin.ignore();

        switch (choice) {
        case 1: {
            cout << "\nDisplaying Catalog:\n";
            bookTree.traverse();
            break;
        }
        case 2: {
            string isbn;
            cout << "\nEnter ISBN to search: ";
            getline(cin, isbn);
            Book searchBook("", "", isbn, "");
            BTreeNode<Book, 100>* node = bookTree.search(searchBook);
            if (node != nullptr) {
                cout << "Book found: ";
                Book foundBook = node->keys[0];
                foundBook.display();
            }
            else {
                cout << "Book with ISBN " << isbn << " not found.\n";
            }
            break;
        }
        case 3: {
            string title, author, isbn, date;
            cout << "\nEnter book title: ";
            getline(cin, title);
            cout << "Enter book author: ";
            getline(cin, author);
            cout << "Enter book ISBN: ";
            getline(cin, isbn);
            cout << "Enter book publication date: ";
            getline(cin, date);
            bookTree.insert(Book(title, author, isbn, date));
            cout << "Book inserted successfully.\n";
            break;
        }
        case 4: {
            string isbn;
            cout << "\nEnter ISBN of the book to delete: ";
            getline(cin, isbn);
            Book removeBook("", "", isbn, "");
            BTreeNode<Book, 100>* result = bookTree.search(removeBook);

            if (result == nullptr)
            {
                cout << "Book with ISBN " << isbn << " not found.\n";
            }
            else {
                bookTree.remove(removeBook);
                cout << "Book removed successfully.\n";
            }
            break;
        }
        case 5: {
            cout << "\nModify book information\n";
            string isbn, title, author, date;
            cout << "\nEnter ISBN of the book to be modified: ";
            getline(cin, isbn);
            cout << "\nHit enter if there is no change in information for respective categories";
            cout << "\nEnter new title: ";
            getline(cin, title);
            cout << "Enter new book author: ";
            getline(cin, author);
            cout << "Enter new book ISBN: ";
            getline(cin, isbn);
            cout << "Enter new book publication date: ";
            getline(cin, date);
            int val = bookTree.modifyBook(isbn, title, author, date);
            if (val == 1)
            {
                std::cout << "Book details updated successfully!" << std::endl;
            }
            else {
                cout << "Book was not found" << std::endl;
            }
            break;
        }
        case 6: {
            cout << "\nExiting program. Goodbye!\n";
            break;
        }
        default: {
            cout << "\nInvalid choice. Please try again.\n";
        }
        }
    } while (choice != 6);
    return 0;
}