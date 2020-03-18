//
// Created by golde on 3/13/2020.
//

#ifndef SPELLER_TRIE_H
#define SPELLER_TRIE_H

#include <string>
#include <vector>

static const int alphabet = 27;

class TrieNode {
private:
public:
    bool isComplete;

    TrieNode *children[alphabet];

    TrieNode() : isComplete(false),children() {};
};

class trie {
private:
    TrieNode *root;

    static void printNode(const TrieNode *node, std::vector<char> *tempoWord = {});

public:
    trie();

    ~trie();

    TrieNode *getRoot();

    void insert(const std::string &element);

    bool find(const std::string &element);

    void erase(std::string element);

    void print();
};


#endif //SPELLER_TRIE_H
