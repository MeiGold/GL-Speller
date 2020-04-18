//
// Created by golde on 3/13/2020.
//

#include <fstream>
#include <sstream>
#include <random>
#include <algorithm>
#include <chrono>
#include "binaryTreeChecker.h"


void binaryTreeChecker::add(std::string element) {
    container.add(element);
}

bool binaryTreeChecker::check(std::string element) {
    return container.find(element);
}

void binaryTreeChecker::createDictionary(std::vector<std::string> words) {
    auto start = std::chrono::steady_clock::now();
    // random uniform shuffle
    std::random_device rd;
    std::mt19937 g(rd());

    std::shuffle(words.begin(), words.end(), g);
    auto end = std::chrono::steady_clock::now();
    std::chrono::duration<double> elapsed_seconds = end - start;
    std::cout << "(shuffle - "
              << std::chrono::duration_cast<std::chrono::milliseconds>(elapsed_seconds).count() << ") ";
    for (const auto &word:words) {
        container.add(word);
    }
}

binaryTreeChecker::~binaryTreeChecker() {

}
