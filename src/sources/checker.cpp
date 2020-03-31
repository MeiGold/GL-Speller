//
// Created by golde on 3/12/2020.
//

#include "../headers/checker.h"
#include <algorithm>

std::string checker::checkWord(std::string &word) {
    //it allows all words like [(,', "]a-z[',', '.', !, ?, ), ;, :, ", ']
    //not any combination of symbols awae2131`21aw will be a valid word

    // convert string to lower case
    std::for_each(word.begin(), word.end(), [](char &c) {
        c = ::tolower(c);
    });

    switch (word[0]) {
        case '(':
        case '\'':
        case '"':
            word.erase(word.begin());
            break;
        default:
            break;
    }

    for (int i = 0; i < word.length() - 1; ++i) {
        if (word[i] < 97 || word[i] > 122) {
            if (word[i] == 39)continue;
            return "";
        }
    }

    if (word.length() == 1) {
        if (word[0] < 97 || word[0] > 122)return "";
        else return word;

    }

    char c = word[word.length() - 1];

    switch (c) {
        case ',':
        case '.' :
        case '!':
        case '?':
        case ')':
        case ';':
        case ':':
        case '"':
        case '\'':
            word.erase(word.end() - 1);
            break;
        default:
            if (c < 97 || c > 122)
                return "";
            break;

    }

    return word;
}

