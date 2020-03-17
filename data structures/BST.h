//
// Created by golde on 3/13/2020.
//

#ifndef SPELLER_BST_H
#define SPELLER_BST_H

template<class T>
class Node {
public:
    Node *left;
    Node *right;
    T value;

    Node() : left(nullptr), right(nullptr), value(nullptr) {}

    Node(T value) : left(nullptr), right(nullptr), value(value) {}
};

template<class T>
class BST {
private:
    Node<T> *root;

    void addInTree(Node<T> *node, T value);

    bool findInTree(Node<T> *node, T value);

    void deleteNode(Node<T> *node);

public:
    BST();

    BST(Node<T> *root);

    ~BST();

    void add(T value);

    static void inOrderOutput(const Node<T> *node);

    Node<T> *getRoot() const;

    int treeLength(const Node<T> *node) const;

    bool find(T elem);
};

#include "BST.cpp"


#endif //SPELLER_BST_H
