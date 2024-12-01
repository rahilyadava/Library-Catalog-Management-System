#include "Book.h"
#include <iostream>

Book::Book(std::string title, std::string author, int isbn, std::string date)
    : title(title), author(author), isbn(isbn), date(date) {}

bool Book::operator<(const Book& other) const {
    return isbn < other.isbn;
}

bool Book::operator>(const Book& other) const {
    return isbn > other.isbn;
}

bool Book::operator==(const Book& other) const {
    return isbn == other.isbn;
}

// Getter for title
std::string Book::getTitle() const {
    return title;
}

// Getter for author
std::string Book::getAuthor() const {
    return author;
}

// Getter for ISBN
int Book::getISBN() const {
    return isbn;
}

// Getter for date
std::string Book::getDate() const {
    return date;
}

// Setter for title
void Book::setTitle(const std::string& newTitle) {
    title = newTitle;
}

// Setter for author
void Book::setAuthor(const std::string& newAuthor) {
    author = newAuthor;
}

// Setter for ISBN
void Book::setISBN(int newISBN) {
    isbn = newISBN;
}

// Setter for date
void Book::setDate(const std::string& newDate) {
    date = newDate;
}

void Book::display() const {
    std::cout << "Title: " << title 
              << ", Author: " << author 
              << ", ISBN: " << isbn 
              << ", Publication Date: " << date << std::endl;
}