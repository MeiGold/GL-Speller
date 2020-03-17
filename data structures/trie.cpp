//
// Created by golde on 3/13/2020.
//

#include <algorithm>
#include <iostream>
#include "trie.h"

TrieNode *trie::getRoot() {
    return root;
}

void trie::insert(const std::string &element) {
    TrieNode *current = root;
    for (const char &e : element
            ) {
        if (e == '\'') {
            if (current->children[26] == nullptr) {
                current->children[26] = new TrieNode();
            }
            current = current->children[26];
            continue;
        }
        if (current->children[e - 'a'] == nullptr) {
            current->children[e - 'a'] = new TrieNode();
        }
        current = current->children[e - 'a'];

    }
    current->isComplete = true;

}

bool trie::find(const std::string &element) {
    //std::cout<<element<<std::endl;
    TrieNode *current = root;
    for (const char &e : element) {
        if (e == '\'') {
            if (current->children[26]) {
                current = current->children[26];
                continue;
            } else return false;
        }
        if (current->children[e - 'a']) {
            current = current->children[e - 'a'];
        } else return false;
    }
    return current->isComplete;
}

void trie::print() {
    printNode(root);
}

void trie::printNode(const TrieNode *node, std::vector<char> *tempoWord) {
    if (tempoWord == nullptr)tempoWord = new std::vector<char>;
    if (node == nullptr)return;
    if (node->isComplete) {
        for (const char &i: *tempoWord) {
            std::cout << i;
        }
        std::cout << '\n';
    }
    for (int i = 0; i < 27; ++i) {
        if (i == 26) {
            if (node->children[26]) {
                tempoWord->emplace_back('\'');
                printNode(node->children[26], tempoWord);
                tempoWord->pop_back();
                continue;
            }
        }
        if (node->children[i]) {
            tempoWord->emplace_back((char) i + 'a');
            printNode(node->children[i], tempoWord);
            tempoWord->pop_back();
        }
    }
}

trie::trie() {
    root = new TrieNode();
}

trie::~trie() {
    delete root;
}
