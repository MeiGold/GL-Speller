//
// Created by golde on 3/12/2020.
//

#ifndef SPELLER_VECTORCHECKER_H
#define SPELLER_VECTORCHECKER_H


#include "checker.h"
#include <vector>


class vectorChecker : public checker {
private:
    std::vector<std::string> container;
public:
    vectorChecker() = default;
    ~vectorChecker() = default;
    void add(std::string element) override;
    bool check(std::string element) override;
    void createDictionary(std::string filename) override;

};


#endif //SPELLER_VECTORCHECKER_H
