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
    BTree<Book, 1000> bookTree;

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
            int isbn;
            cout << "\nEnter ISBN to search: ";
            cin >> isbn;
            Book searchBook("", "", isbn, "");
            BTreeNode<Book, 1000>* node = bookTree.search(searchBook);
            if (node != nullptr) {
                cout << "Book found: ";
                for (int i = 0; i < node->n; ++i) {
                    if (node->keys[i].getISBN() == searchBook.getISBN()) {
                        Book foundBook = node->keys[i];
                        foundBook.display();
                        break; 
                    }
                }
            }
            else {
                cout << "Book with ISBN " << isbn << " not found.\n";
            }
            break;
        }
        case 3: {
            string title, author, date, word;
            int isbn;
            cout << "\nEnter book title: ";
            getline(cin, title);
            cout << "Enter book author: ";
            getline(cin, author);
            cout << "Enter book ISBN: ";
            getline(cin, word);
            isbn = stoi(word);
            cout << "Enter book publication date: ";
            getline(cin, date);
            bookTree.insert(Book(title, author, isbn, date));
            cout << "Book inserted successfully.\n";
            break;
        }
        case 4: {
            int isbn;
            cout << "\nEnter ISBN of the book to delete: ";
            cin >> isbn;
            Book removeBook("", "", isbn, "");
            BTreeNode<Book, 1000>* result = bookTree.search(removeBook);

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
            string title, author, date, dummy, x;
            int isbn, newisbn;
            cout << "\nEnter ISBN of the book to be modified: ";
            getline(cin, x);
            isbn = stoi(x);
            cout << "\nHit enter or 0 for ISBN if there is no change in information for respective categories";
            cout << "\nEnter new title: ";
            getline(cin, title);
            cout << "Enter new book author: ";
            getline(cin, author);
            cout << "Enter new book ISBN: ";
            getline(cin, dummy); 
            newisbn = stoi(dummy); 
            cout << "Enter new book publication date: ";
            getline(cin, date);
            int val = bookTree.modifyBook(isbn, title, author, newisbn, date);
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