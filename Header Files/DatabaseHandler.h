#ifndef DATABASEHANDLER_H
#define DATABASEHANDLER_H

#include <sqlite3.h>
#include <iostream>
#include <string>
#include "BTree.h"

class DatabaseHandler {
public:
    DatabaseHandler(const std::string& dbName);
    ~DatabaseHandler();

    bool open();
    void close();

    void loadBooksIntoTree(BTree<Book, 1000>& bookTree);
    void insertBook(const Book& book);
    void deleteBook(int isbn);
    void DatabaseHandler::updateBook(int oldIsbn, const std::string& title, const std::string& author, int newIsbn, const std::string& date);
    void displayBooks();

private:
    sqlite3* db;
    std::string dbName;
    int executeQuery(const std::string& query);
};

#endif // DATABASEHANDLER_H