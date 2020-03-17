//
// Created by golde on 3/12/2020.
//

#include <fstream>
#include <iostream>
#include <sstream>
#include <chrono>
#include "vectorChecker.h"

void vectorChecker::add(std::string element) {
    container.emplace_back(element);
}

bool vectorChecker::check(std::string elem) {
    size_t left = 0, right = container.size() - 1;
    size_t index = 0;
    while (left != right && left < right) {
        index = (left + right) / 2;
        if (container[index] == elem)return true;
        std::string tempo = container[index];
        if (container[index] > elem) {
            right = index - 1;
        } else {
            left = index + 1;
        }
    }
    return container[left] == elem;
}

void vectorChecker::createDictionary(std::string filename) {
    std::ifstream in(filename);
    if (!in.is_open()) {
        std::cout << "Failed to open dictionary!" << std::endl;
    } else {
        std::stringstream buffer;
        buffer << in.rdbuf();
        std::string tempoWord;
        while (buffer >> tempoWord) {
            tempoWord = checkWord(tempoWord);
            if (!tempoWord.empty())container.emplace_back(tempoWord);
        }
    }
}

