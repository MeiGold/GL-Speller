//
// Created by golde on 3/13/2020.
//

#include <fstream>
#include <iostream>
#include <sstream>
#include "../../include/trieChecker.h"

void trieChecker::add(std::string element) {
    container.insert(element);
}

bool trieChecker::check(std::string element) {
    return container.find(element);
}

void trieChecker::createDictionary(std::string filename) {
    std::ifstream in(filename);
    if (!in.is_open()) {
        std::cout << "Failed to open dictionary!" << std::endl;
    } else {
        std::stringstream buffer;
        buffer << in.rdbuf();
        std::string tempoWord;
        while (buffer >> tempoWord) {
            tempoWord = checkWord(tempoWord);
            if (tempoWord == "they'll") {
                container.insert(tempoWord);
            }
            if (!tempoWord.empty())container.insert(tempoWord);
        }
    }
}
