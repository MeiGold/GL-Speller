//
// Created by golde on 3/12/2020.
//

#ifndef SPELLER_CHECKER_H
#define SPELLER_CHECKER_H

#include <vector>
#include <string>

class checker {
public:
    virtual ~checker() = default;

    virtual void add(std::string element) = 0;

    virtual bool check(std::string element) = 0;

    virtual void createDictionary(std::vector<std::string> words) = 0;

    static std::string checkWord(std::string &word);

};


#endif //SPELLER_CHECKER_H
