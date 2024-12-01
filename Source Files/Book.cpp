#include "Book.h"
#include <iostream>

Book::Book(std::string title, std::string author, std::string isbn, std::string date)
    : title(title), author(author), isbn(isbn), date{date}

bool Book::operator<(const Book& other) const {
    return isbn < other.isbn;
}

bool Book::operator>(const Book& other) const {
    return isbn > other.isbn;
}

bool Book::operator==(const Book& other) const {
    return isbn == other.isbn;
}

void Book::display() const {
    std::cout << "Title: " << title 
              << ", Author: " << author 
              << ", ISBN: " << isbn 
              << ", Publication Date: " << date << std::endl;
}