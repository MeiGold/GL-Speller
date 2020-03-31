//
// Created by golde on 3/13/2020.
//

#ifndef SPELLER_UNORDEREDMAPCHECKER_H
#define SPELLER_UNORDEREDMAPCHECKER_H


#include <unordered_map>
#include <string>
#include <functional>
#include "../src/headers/checker.h"

class unorderedMapChecker : public checker {
private:
    std::unordered_map<std::string, std::string> container;
public:
    unorderedMapChecker() = default;

    ~unorderedMapChecker() = default;

    void add(std::string element) override;

    bool check(std::string element) override;

    void createDictionary(std::vector<std::string> words) override;
};


#endif //SPELLER_UNORDEREDMAPCHECKER_H
