//
// Created by golde on 3/13/2020.
//
#ifndef SPELLER_HASHTABLECHECKER_H
#define SPELLER_HASHTABLECHECKER_H


#include "checker.h"
#include "MurmurHash2.h"

class hashTableChecker : public checker {
private:
    MurmurHash2<std::string> *container;
public:
    hashTableChecker(int size);
    ~hashTableChecker() = default;
    void add(std::string element) override;
    bool check(std::string element) override;
    void createDictionary(std::string filename) override;
};



#endif //SPELLER_HASHTABLECHECKER_H
