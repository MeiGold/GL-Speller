//
// Created by golde on 3/13/2020.
//

#ifndef SPELLER_TRIECHECKER_H
#define SPELLER_TRIECHECKER_H


#include "checker.h"
#include "trie.h"

class trieChecker : public checker {
private:
    trie container;
public:
    trieChecker() = default;

    ~trieChecker() override = default;

    void add(std::string element) override;

    bool check(std::string element) override;

    void createDictionary(std::vector<std::string> words) override;
};


#endif //SPELLER_TRIECHECKER_H
