#ifndef BOOK_H
#define BOOK_H

#include <string>

class Book {
public:
    std::string title;
    std::string author;
    std::string isbn;
    std::string date;

    // Constructor
    Book(std::string title = "", std::string author = "", std::string isbn = "", std::string date="");

    // Comparison operators for sorting based on ISBN
    bool operator<(const Book& other) const;
    bool operator>(const Book& other) const;
    bool operator==(const Book& other) const;

    // Display function
    void display() const;
};

#endif // BOOK_H
