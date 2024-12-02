#include "DatabaseHandler.h"

// Constructor to initialize database name
DatabaseHandler::DatabaseHandler(const std::string& dbName) : dbName(dbName), db(nullptr) {}

// Destructor to close the database connection
DatabaseHandler::~DatabaseHandler() {
    if (db != nullptr) {
        close();
    }
}

// Open a connection to the SQLite database
bool DatabaseHandler::open() {
    if (sqlite3_open(dbName.c_str(), &db) != SQLITE_OK) {
        std::cerr << "Cannot open database: " << sqlite3_errmsg(db) << std::endl;
        return false;
    }
    return true;
}

// Close the database connection
void DatabaseHandler::close() {
    if (db != nullptr) {
        sqlite3_close(db);
    }
}

// Load all books from the database and insert into the B-tree
void DatabaseHandler::loadBooksIntoTree(BTree<Book, 1000>& bookTree) {
    const char* query = "SELECT title, author, isbn, date FROM books;";
    sqlite3_stmt* stmt;
    if (sqlite3_prepare_v2(db, query, -1, &stmt, nullptr) == SQLITE_OK) {
        while (sqlite3_step(stmt) == SQLITE_ROW) {
            std::string title = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
            std::string author = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
            int isbn = sqlite3_column_int(stmt, 2);
            std::string date = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3));
            Book book(title, author, isbn, date);
            bookTree.insert(book);
        }
        sqlite3_finalize(stmt);
    } else {
        std::cerr << "Error loading books into tree: " << sqlite3_errmsg(db) << std::endl;
    }
}

// Insert a new book into the database
void DatabaseHandler::insertBook(const Book& book) {
    std::string query = "INSERT INTO books (title, author, isbn, date) VALUES ('" +
                        book.getTitle() + "', '" + book.getAuthor() + "', " +
                        std::to_string(book.getISBN()) + ", '" + book.getDate() + "');";
    executeQuery(query);
}

// Delete a book from the database using its ISBN
void DatabaseHandler::deleteBook(int isbn) {
    std::string query = "DELETE FROM books WHERE isbn = " + std::to_string(isbn) + ";";
    executeQuery(query);
}

// Update a book's details in the database
void DatabaseHandler::updateBook(int oldIsbn, const std::string& title, const std::string& author, int newIsbn, const std::string& date) {
    std::string query = 
            "UPDATE books "
            "SET title = '" + title + 
            "', author = '" + author + 
            "', date = '" + date + 
            "', isbn = CASE WHEN isbn = 0 THEN " + std::to_string(newIsbn) + " ELSE isbn END "
            "WHERE isbn = " + std::to_string(oldIsbn) + ";";

        executeQuery(query);
}
// Execute a query (for insert, delete, update)
int DatabaseHandler::executeQuery(const std::string& query) {
    char* errMsg;
    int result = sqlite3_exec(db, query.c_str(), nullptr, nullptr, &errMsg);
    if (result != SQLITE_OK) {
        std::cerr << "SQL error: " << errMsg << std::endl;
        sqlite3_free(errMsg);
    }
    return result;
}

// Display all books in the database (for debugging or visual check)
void DatabaseHandler::displayBooks() {
    const char* query = "SELECT title, author, isbn, date FROM books;";
    sqlite3_stmt* stmt;
    if (sqlite3_prepare_v2(db, query, -1, &stmt, nullptr) == SQLITE_OK) {
        while (sqlite3_step(stmt) == SQLITE_ROW) {
            std::string title = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
            std::string author = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
            int isbn = sqlite3_column_int(stmt, 2);
            std::string date = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3));
            std::cout << "Title: " << title << ", Author: " << author << ", ISBN: " << isbn << ", Date: " << date << std::endl;
        }
        sqlite3_finalize(stmt);
    } else {
        std::cerr << "Error displaying books: " << sqlite3_errmsg(db) << std::endl;
    }
}