//
// Created by golde on 3/13/2020.
//

#include <iostream>
#include "BST.h"

template<class T>
BST<T>::BST() : root(nullptr) {}

template<class T>
BST<T>::BST(Node<T> *root) : root(root) {}

template<class T>
BST<T>::~BST() {
    deleteNode(root);
}

template<class T>
void BST<T>::addInTree(Node<T> *node, T value) {
    if (node->value == value) {
        return;
    }
    if (value < node->value) {
        if (!node->left) {
            node->left = new Node<T>(value);
        } else {
            addInTree(node->left, value);
        }
    } else if (value > node->value) {
        if (!node->right) {
            node->right = new Node<T>(value);
        } else {
            addInTree(node->right, value);
        }
    }
}

template<class T>
void BST<T>::add(T value) {
    if (!root) {
        root = new Node<T>(value);
    } else addInTree(root, value);
}

template<class T>
void BST<T>::inOrderOutput(const Node<T> *node) {
    if (!node)return;
    if (node->left)inOrderOutput(node->left);
    std::cout << node->value << std::endl;
    if (node->right)inOrderOutput(node->right);
}

template<class T>
Node<T> *BST<T>::getRoot() const {
    return root;
}

template<class T>
int BST<T>::treeLength(const Node<T> *const node) const {
    if (node == nullptr)
        return 0;
    else {
        /* compute the depth of each subtree */
        int lDepth = treeLength(node->left);
        int rDepth = treeLength(node->right);

        /* use the larger one */
        if (lDepth > rDepth)
            return (lDepth + 1);
        else return (rDepth + 1);
    }
}

template<class T>
bool BST<T>::find(T elem) {
    return findInTree(root, elem);
}

template<class T>
bool BST<T>::findInTree(Node<T> *node, T value) {
    while (node->value != value) {// find element to delete
        if (value < node->value) {
            if (node->left) {
                node = node->left;
            } else break;
        } else if (value > node->value) {
            if (node->right) {
                node = node->right;
            } else break;
        }
    }
    return node->value == value;
}

template<class T>
void BST<T>::deleteNode(Node<T> *node) {
    if (node) {
        deleteNode(node->left);
        deleteNode(node->right);
        delete node;
    }
}
