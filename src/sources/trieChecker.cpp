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

void trieChecker::createDictionary(std::vector<std::string> words) {
    for (const auto &word:words) {
        container.insert(word);
    }
}
