//
// Created by golde on 3/13/2020.
//

#include <fstream>
#include <sstream>
#include <random>
#include <algorithm>
#include "binaryTreeChecker.h"

using string = std::string;

void binaryTreeChecker::add(std::string element) {
    container.add(element);
}


bool binaryTreeChecker::check(std::string element) {
    return container.find(element);
}

void binaryTreeChecker::createDictionary(std::string filename) {
    std::ifstream in(filename);
    if (!in.is_open()) {
        std::cout << "Failed to open dictionary!" << std::endl;
    } else {
        std::vector<std::string> words;
        std::stringstream buffer;
        buffer << in.rdbuf();
        std::string tempoWord;
        while (buffer >> tempoWord) {
            tempoWord = checkWord(tempoWord);
            if (!tempoWord.empty())words.emplace_back(tempoWord);
        }
        // random uniform shuffle
        std::random_device rd;
        std::mt19937 g(rd());

        std::shuffle(words.begin(), words.end(), g);
        size_t size = words.size();
        for (const auto &word : words) {
            container.add(word);
        }

    }
}
