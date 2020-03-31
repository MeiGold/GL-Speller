//
// Created by golde on 3/13/2020.
//

#include <fstream>
#include <iostream>
#include <sstream>
#include "../../include/unorderedMapChecker.h"

void unorderedMapChecker::add(std::string element) {
    container[element] = element;
}

bool unorderedMapChecker::check(std::string element) {
    auto iterator = container.find(element);
    return iterator != container.end();
}

void unorderedMapChecker::createDictionary(std::vector<std::string> words) {
    for (const auto &word:words) {
        container[word] = word;
    }
}
