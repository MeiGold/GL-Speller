//
// Created by golde on 3/13/2020.
//

#include <fstream>
#include <iostream>
#include <sstream>
#include "unorderedMapChecker.h"

void unorderedMapChecker::add(std::string element) {
    container[element] = element;
}

bool unorderedMapChecker::check(std::string element) {
    auto iterator = container.find(element);
    return iterator != container.end();
}

void unorderedMapChecker::createDictionary(std::string filename) {
    std::ifstream in(filename);
    if (!in.is_open()) {
        std::cout << "Failed to open dictionary!" << std::endl;
    } else {
        std::stringstream buffer;
        buffer << in.rdbuf();
        std::string tempoWord;
        while (buffer >> tempoWord) {
            tempoWord = checkWord(tempoWord);
            if (!tempoWord.empty())container[tempoWord] = tempoWord;
        }

    }
}
