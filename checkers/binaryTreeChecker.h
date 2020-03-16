//
// Created by golde on 3/13/2020.
//

#ifndef SPELLER_BINARYTREECHECKER_H
#define SPELLER_BINARYTREECHECKER_H


#include "checker.h"
#include "BST.h"
#include <string>


class binaryTreeChecker: public checker {
private:
    BST<std::string> container;
public:
    binaryTreeChecker() = default;
    ~binaryTreeChecker() = default;
    void add(std::string element) override;
    bool check(std::string element) override;
    void createDictionary(std::string filename) override;
};


#endif //SPELLER_BINARYTREECHECKER_H
