#include "BTree.h"

int main() {
    BTree<Book, 100> bookTree;

    // Create books
    Book b1("To Kill a Mockingbird", "Harper Lee", "9780061120084");
    Book b2("1984", "George Orwell", "9780451524935");
    Book b3("The Great Gatsby", "F. Scott Fitzgerald", "9780743273565");
    Book b4("The Catcher in the Rye", "J.D. Salinger", "9780316769488");
    Book b5("Moby Dick", "Herman Melville", "9781503280786");

    // Insert books into the tree
    bookTree.insert(b1);
    bookTree.insert(b2);
    bookTree.insert(b3);
    bookTree.insert(b4);
    bookTree.insert(b5);

    cout << "Books in the tree (in-order traversal):\n";
    bookTree.traverse();

    string isbnToRemove = "9780451524935";
    Book removeBook("", "", isbnToRemove);
    cout << "\nRemoving book with ISBN: " << isbnToRemove << endl;
    bookTree.remove(removeBook);

    cout << "\nBooks after removal:\n";
    bookTree.traverse();

    return 0;
}
