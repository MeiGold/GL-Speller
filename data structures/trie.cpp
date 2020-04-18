//
// Created by golde on 3/13/2020.
//

#include "trie.h"
#include <algorithm>
#include <iostream>

namespace {
    const int trieNodeSize = 26;
}

TrieNode *trie::getRoot() {
    return root;
}

void trie::insert(const std::string &element) {
    TrieNode *current = root;
    for (const char &e : element
            ) {
        if (e == '\'') {
            if (current->children[trieNodeSize] == nullptr) {
                current->children[trieNodeSize] = new TrieNode();
            }
            current = current->children[trieNodeSize];
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
    TrieNode *current = root;
    for (const char &e : element) {
        if (e == '\'') {
            if (current->children[trieNodeSize] != nullptr) {
                current = current->children[trieNodeSize];
                continue;
            }
            return false;
        }
        if (current->children[e - 'a'] != nullptr) {
            current = current->children[e - 'a'];
        } else return false;
    }
    return current->isComplete;
}

void trie::print() {
    printNode(root);
}

void trie::printNode(const TrieNode *node, std::vector<char> tempoWord) {
    //if (tempoWord.empty()) { tempoWord = std::vector<char>{}; }
    if (node == nullptr) { return; }
    if (node->isComplete) {
        for (const char &i: tempoWord) {
            std::cout << i;
        }
        std::cout << '\n';
    }
    for (int i = 0; i < 27; ++i) {
        if (i == trieNodeSize) {
            if (node->children[trieNodeSize]) {
                tempoWord.emplace_back('\'');
                printNode(node->children[trieNodeSize], tempoWord);
                tempoWord.pop_back();
                continue;
            }
        }
        if (node->children[i]) {
            tempoWord.emplace_back((char) i + 'a');
            printNode(node->children[i], tempoWord);
            tempoWord.pop_back();
        }
    }
}

trie::trie() {
    root = new TrieNode();
}

trie::~trie() {
    erase(root);
}

void trie::erase(TrieNode *node) {
    if (node) {
        for (auto &child : node->children) {
            if (child) {
                erase(child);
            }
        }
        delete node;

    }
}




