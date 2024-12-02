#ifndef DATABASEHANDLER_H
#define DATABASEHANDLER_H

#include <sqlite3.h>
#include <string>
#include <iostream>
#include "Book.h"
#include "BTree.h"

class DatabaseHandler {
public:
	// Constructor and Destructor
	DatabaseHandler(const std::string& dbName);
	~DatabaseHandler();

	// Database operations
	bool openDatabase();
	void closeDatabase();
	bool insertBook(const Book& book);
	bool removeBook(const std::string& isbn);
	bool updateBook(const Book& book);
	void loadBooksIntoBTree(BTree<Book, 1000>& bookTree);

private:
	sqlite3* db;  // Database connection
	std::string dbName;  // Database name

	// Helper function to handle errors
	static int callback(void* data, int argc, char** argv, char** azColName);
};

// Constructor
DatabaseHandler::DatabaseHandler(const std::string& dbName) : dbName(dbName), db(nullptr) {}

// Destructor
DatabaseHandler::~DatabaseHandler() {
	closeDatabase();
}

// Open the database
bool DatabaseHandler::openDatabase() {
	if (sqlite3_open(dbName.c_str(), &db)) {
		std::cerr << "Can't open database: " << sqlite3_errmsg(db) << std::endl;
		return false;
	}
	return true;
}

// Close the database
void DatabaseHandler::closeDatabase() {
	if (db) {
		sqlite3_close(db);
		db = nullptr;
	}
}

// Insert a new book into the database
bool DatabaseHandler::insertBook(const Book& book) {
	std::string sql = "INSERT INTO books (isbn, title, author, publicationDate) VALUES ('" +
		book.getISBN() + "', '" + book.getTitle() + "', '" + book.getAuthor() +
		"', '" + book.getPublicationDate() + "');";

	char* errMsg = nullptr;
	if (sqlite3_exec(db, sql.c_str(), nullptr, nullptr, &errMsg) != SQLITE_OK) {
		std::cerr << "SQL error: " << errMsg << std::endl;
		sqlite3_free(errMsg);
		return false;
	}
	return true;
}

// Remove a book from the database
bool DatabaseHandler::removeBook(const std::string& isbn) {
	std::string sql = "DELETE FROM books WHERE isbn = '" + isbn + "';";

	char* errMsg = nullptr;
	if (sqlite3_exec(db, sql.c_str(), nullptr, nullptr, &errMsg) != SQLITE_OK) {
		std::cerr << "SQL error: " << errMsg << std::endl;
		sqlite3_free(errMsg);
		return false;
	}
	return true;
}

// Update a book's information in the database
bool DatabaseHandler::updateBook(const Book& book) {
	std::string sql = "UPDATE books SET title = '" + book.getTitle() + "', author = '" +
		book.getAuthor() + "', publicationDate = '" + book.getPublicationDate() +
		"' WHERE isbn = '" + book.getISBN() + "';";

	char* errMsg = nullptr;
	if (sqlite3_exec(db, sql.c_str(), nullptr, nullptr, &errMsg) != SQLITE_OK) {
		std::cerr << "SQL error: " << errMsg << std::endl;
		sqlite3_free(errMsg);
		return false;
	}
	return true;
}

// Load books from the database into a B-tree
void DatabaseHandler::loadBooksIntoBTree(BTree<Book, 1000>& bookTree) {
	std::string sql = "SELECT * FROM books;";
	char* errMsg = nullptr;

	// Query the database and process the results
	if (sqlite3_exec(db, sql.c_str(), callback, &bookTree, &errMsg) != SQLITE_OK) {
		std::cerr << "SQL error: " << errMsg << std::endl;
		sqlite3_free(errMsg);
	}
}

// Callback function to process the results from the database
int DatabaseHandler::callback(void* data, int argc, char** argv, char** azColName) {
	BTree<Book, 1000>* bookTree = reinterpret_cast<BTree<Book, 1000>*>(data);

	// Assuming argv[0] = ISBN, argv[1] = title, argv[2] = author, argv[3] = publicationDate
	Book book(argv[1], argv[2], argv[0], argv[3]);
	bookTree->insert(book);  // Insert into B-tree

	return 0;
}

#endif // DATABASEHANDLER_H

