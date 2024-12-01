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

    // Getters
    std::string getTitle() const;
    std::string getAuthor() const;
    std::string getISBN() const;
    std::string getDate() const;

    // Setters
    void setTitle(const std::string& newTitle);
    void setAuthor(const std::string& newAuthor);
    void setISBN(const std::string& newISBN);
    void setDate(const std::string& newDate);

    // Display function
    void display() const;
};

#endif // BOOK_H