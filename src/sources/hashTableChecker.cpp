//
// Created by golde on 3/13/2020.
//

#include <fstream>
#include <iostream>
#include <sstream>
#include "hashTableChecker.h"

hashTableChecker::hashTableChecker(int size) {
    container = new MurmurHash2<std::string>(size);
}

void hashTableChecker::add(std::string element) {
    container->insertElement(element, element.length());
}

bool hashTableChecker::check(std::string element) {
    return container->checkElement(element, element.length());
}

void hashTableChecker::createDictionary(std::vector<std::string> words) {
    for (const auto &word:words) {
        container->insertElement(word, word.length());
    }
}

hashTableChecker::~hashTableChecker() {
    delete container;
}
