#include <iostream>
#include <string>
#include "Book.h"

using namespace std;

// Node class for B-Tree
template <typename T, int ORDER>
class BTreeNode {
public:
    T keys[ORDER - 1];        // Array of keys (Books in this case)
    BTreeNode* children[ORDER]; // Array of child pointers
    int n;                    // Current number of keys
    bool leaf;                // True if leaf node, false otherwise

    BTreeNode(bool isLeaf = true) : n(0), leaf(isLeaf) {
        for (int i = 0; i < ORDER; i++)
            children[i] = nullptr;
    }
};

// BTree class
template <typename T, int ORDER>
class BTree {
private:
    BTreeNode<T, ORDER>* root;

    // Function to split a full child node
    void splitChild(BTreeNode<T, ORDER>* x, int i) {
        BTreeNode<T, ORDER>* y = x->children[i];
        BTreeNode<T, ORDER>* z = new BTreeNode<T, ORDER>(y->leaf);
        z->n = ORDER / 2 - 1;

        for (int j = 0; j < ORDER / 2 - 1; j++)
            z->keys[j] = y->keys[j + ORDER / 2];

        if (!y->leaf) {
            for (int j = 0; j < ORDER / 2; j++)
                z->children[j] = y->children[j + ORDER / 2];
        }

        y->n = ORDER / 2 - 1;

        for (int j = x->n; j >= i + 1; j--)
            x->children[j + 1] = x->children[j];

        x->children[i + 1] = z;

        for (int j = x->n - 1; j >= i; j--)
            x->keys[j + 1] = x->keys[j];

        x->keys[i] = y->keys[ORDER / 2 - 1];
        x->n = x->n + 1;
    }

    // Function to insert a key in a non-full node
    void insertNonFull(BTreeNode<T, ORDER>* x, T k) {
        int i = x->n - 1;

        if (x->leaf) {
            while (i >= 0 && k < x->keys[i]) {
                x->keys[i + 1] = x->keys[i];
                i--;
            }

            x->keys[i + 1] = k;
            x->n = x->n + 1;
        }
        else {
            while (i >= 0 && k < x->keys[i])
                i--;

            i++;
            if (x->children[i]->n == ORDER - 1) {
                splitChild(x, i);

                if (k > x->keys[i])
                    i++;
            }
            insertNonFull(x->children[i], k);
        }
    }

    // Function to traverse the tree
    void traverse(BTreeNode<T, ORDER>* x) {
        int i;
        for (i = 0; i < x->n; i++) {
            if (!x->leaf)
                traverse(x->children[i]);
            x->keys[i].display(); // Display book info
        }

        if (!x->leaf)
            traverse(x->children[i]);
    }

    BTreeNode<T, ORDER>* search(BTreeNode<T, ORDER>* x, T k) {
        int i = 0;
        while (i < x->n && k > x->keys[i])
            i++;

        if (i < x->n && k == x->keys[i])
            return x;

        if (x->leaf)
            return nullptr;

        return search(x->children[i], k);
    }

    // Function to find the predecessor of a node
    T getPredecessor(BTreeNode<T, ORDER>* node, int idx) {
        BTreeNode<T, ORDER>* current = node->children[idx];
        while (!current->leaf)
            current = current->children[current->n];
        return current->keys[current->n - 1];
    }

    // Function to find the successor of a node
    T getSuccessor(BTreeNode<T, ORDER>* node, int idx) {
        BTreeNode<T, ORDER>* current = node->children[idx + 1];
        while (!current->leaf)
            current = current->children[0];
        return current->keys[0];
    }

    // Function to fill child node
    void fill(BTreeNode<T, ORDER>* node, int idx) {
        if (idx != 0 && node->children[idx - 1]->n >= ORDER / 2)
            borrowFromPrev(node, idx);
        else if (idx != node->n && node->children[idx + 1]->n >= ORDER / 2)
            borrowFromNext(node, idx);
        else {
            if (idx != node->n)
                merge(node, idx);
            else
                merge(node, idx - 1);
        }
    }

    // Function to borrow a key from the previous sibling
    void borrowFromPrev(BTreeNode<T, ORDER>* node, int idx) {
        BTreeNode<T, ORDER>* child = node->children[idx];
        BTreeNode<T, ORDER>* sibling = node->children[idx - 1];

        for (int i = child->n - 1; i >= 0; --i)
            child->keys[i + 1] = child->keys[i];

        if (!child->leaf) {
            for (int i = child->n; i >= 0; --i)
                child->children[i + 1] = child->children[i];
        }

        child->keys[0] = node->keys[idx - 1];

        if (!child->leaf)
            child->children[0] = sibling->children[sibling->n];

        node->keys[idx - 1] = sibling->keys[sibling->n - 1];

        child->n += 1;
        sibling->n -= 1;
    }

    // Function to borrow a key from the next sibling
    void borrowFromNext(BTreeNode<T, ORDER>* node, int idx) {
        BTreeNode<T, ORDER>* child = node->children[idx];
        BTreeNode<T, ORDER>* sibling = node->children[idx + 1];

        child->keys[child->n] = node->keys[idx];

        if (!child->leaf)
            child->children[child->n + 1] = sibling->children[0];

        node->keys[idx] = sibling->keys[0];

        for (int i = 1; i < sibling->n; ++i)
            sibling->keys[i - 1] = sibling->keys[i];

        if (!sibling->leaf) {
            for (int i = 1; i <= sibling->n; ++i)
                sibling->children[i - 1] = sibling->children[i];
        }

        child->n += 1;
        sibling->n -= 1;
    }

    // Function to merge two nodes
    void merge(BTreeNode<T, ORDER>* node, int idx) {
        BTreeNode<T, ORDER>* child = node->children[idx];
        BTreeNode<T, ORDER>* sibling = node->children[idx + 1];

        child->keys[ORDER / 2 - 1] = node->keys[idx];

        for (int i = 0; i < sibling->n; ++i)
            child->keys[i + ORDER / 2] = sibling->keys[i];

        if (!child->leaf) {
            for (int i = 0; i <= sibling->n; ++i)
                child->children[i + ORDER / 2] = sibling->children[i];
        }

        for (int i = idx + 1; i < node->n; ++i)
            node->keys[i - 1] = node->keys[i];

        for (int i = idx + 2; i <= node->n; ++i)
            node->children[i - 1] = node->children[i];

        child->n += sibling->n + 1;
        node->n -= 1;

        delete sibling;
    }

    // Function to delete a key from a node
    void deleteKey(BTreeNode<T, ORDER>* node, T k) {
        int idx = 0;
        while (idx < node->n && node->keys[idx] < k)
            idx++;

        if (idx < node->n && node->keys[idx] == k) {
            if (node->leaf) {
                for (int i = idx + 1; i < node->n; ++i)
                    node->keys[i - 1] = node->keys[i];
                node->n--;
            }
            else {
                T pred = getPredecessor(node, idx);
                node->keys[idx] = pred;
                deleteKey(node->children[idx], pred);
            }
        }
        else {
            if (node->leaf) {
                cout << "Book not found.\n";
                return;
            }

            bool flag = (idx == node->n);
            if (node->children[idx]->n < ORDER / 2)
                fill(node, idx);

            if (flag && idx > node->n)
                deleteKey(node->children[idx - 1], k);
            else
                deleteKey(node->children[idx], k);
        }
    }

public:
    BTree() { root = new BTreeNode<T, ORDER>(true); }

    void insert(T k) {
        if (root->n == ORDER - 1) {
            BTreeNode<T, ORDER>* s = new BTreeNode<T, ORDER>(false);
            s->children[0] = root;
            root = s;
            splitChild(s, 0);
            insertNonFull(s, k);
        }
        else
            insertNonFull(root, k);
    }

    void traverse() {
        if (root != nullptr)
            traverse(root);
    }

    BTreeNode<T, ORDER>* search(T k) {
        return (root == nullptr) ? nullptr : search(root, k);
    }

    void remove(T k) {
        if (!root) {
            cout << "The tree is empty\n";
            return;
        }

        deleteKey(root, k);
        if (root->n == 0) {
            BTreeNode<T, ORDER>* tmp = root;
            if (root->leaf)
                root = nullptr;
            else
                root = root->children[0];
            delete tmp;
        }
    }
    int BTree<T, ORDER>::modifyBook(std::string isbn, const std::string& newTitle, const std::string& newAuthor, const std::string& newDate) {
        // Use the search function to find the node containing the book with the given ISBN
        Book searchBook("", "", isbn, "");
        BTreeNode<T, ORDER>* node = search(searchBook);  // search function should return the node containing the book
        if (node != nullptr) {
            // Loop through the node's keys to find the specific book by ISBN
            Book* bookToModify = nullptr;
            for (int i = 0; i < node->n; ++i) {
                if (node->keys[i].getISBN() == isbn) {
                    bookToModify = &node->keys[i]; // Found the book to modify
                    break;
                }
            }
            std::cout << bookToModify->getAuthor() << std::endl;
            // If the book is found, modify the book's details
            if (bookToModify != nullptr) {
                if (!newTitle.empty()) {
                    bookToModify->setTitle(newTitle);
                }
                if (!newAuthor.empty()) {
                    bookToModify->setAuthor(newAuthor);
                }
                if (!newDate.empty()) {
                    bookToModify->setDate(newDate);
                }
                return 1;
            }
        }
    }
};