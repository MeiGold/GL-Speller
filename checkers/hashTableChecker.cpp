//
// Created by golde on 3/13/2020.
//

#include <fstream>
#include <iostream>
#include <sstream>
#include "hashTableChecker.h"

hashTableChecker::hashTableChecker(int size) {
    container = new MurmurHash2<std::string> (size);
}

void hashTableChecker::add(std::string element) {
    container->insertElement(element, element.length());
}

bool hashTableChecker::check(std::string element) {
    return container->checkElement(element, element.length());
}

void hashTableChecker::createDictionary(std::string filename) {
    std::ifstream in(filename);
    if (!in.is_open()) {
        std::cout << "Failed to open dictionary!" << std::endl;
    } else {
        std::stringstream buffer;
        buffer << in.rdbuf();
        std::string tempoWord;
        while (buffer >> tempoWord) {
            tempoWord = checkWord(tempoWord);
            if (!tempoWord.empty())container->insertElement(tempoWord,tempoWord.length());
        }
    }
}
