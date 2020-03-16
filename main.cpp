#include <iostream>
#include "checker.h"
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <dirent.h>
#include <sstream>
#include <chrono>
#include <binaryTreeChecker.h>
#include <hashTableChecker.h>
#include <unorderedMapChecker.h>
#include <trieChecker.h>
#include "BST.h"
#include "MurmurHash2.h"
#include "trie.h"
#include "vectorChecker.h"

// variable defining path to texts to be checked
static const std::string dictionaryPath = "../dictionary.txt";
static const char *absolutePathToTexts = R"(C:\Users\golde\CLionProjects\GL basecamp\Speller\texts\)";

void checkFiles(const std::vector<std::string> &files, checker* checker);

int main() {
    std::vector<std::string> files;
    DIR *dir;
    struct dirent *ent;
    if ((dir = opendir(absolutePathToTexts)) != nullptr) {
        /* print all the files and directories within directory */
        while ((ent = readdir(dir)) != nullptr) {
            //printf("%s\n", ent->d_name);
            if (strncmp(ent->d_name, ".", 2) != 0 && strncmp(ent->d_name, "..", 3) != 0)
                files.emplace_back(ent->d_name);
        }
        closedir(dir);
    } else {
        /* could not open directory */
        perror("");
        return EXIT_FAILURE;
    }
    std::cout<<"Speller-----------------------------"<<std::endl;
    checker *checker;

    checker = new vectorChecker();
    std::cout<<"stdvector ";
    checkFiles(files,checker);

    checker = new binaryTreeChecker();
    std::cout<<"BST ";
    checkFiles(files,checker);

    checker = new hashTableChecker(2000000);
    std::cout<<"hashTable ";
    checkFiles(files,checker);

    checker = new unorderedMapChecker();
    std::cout<<"unorderedHashMap ";
    checkFiles(files,checker);

    checker = new trieChecker();
    std::cout<<"trie ";
    checkFiles(files,checker);

    return 0;
}

void checkFiles(const std::vector<std::string> &files, checker * const checker){
    auto start = std::chrono::steady_clock::now();
    checker->createDictionary(dictionaryPath);
    auto end = std::chrono::steady_clock::now();
    std::chrono::duration<double> elapsed_seconds = end - start;
    std::cout
            << std::chrono::duration_cast<std::chrono::milliseconds>(elapsed_seconds).count() << " ";
    auto startCheck = std::chrono::steady_clock::now();
    int checkedWords = 0;
    int wrongWords = 0;
    for (const auto &file : files) {
        std::ifstream in(absolutePathToTexts + file);
        if (!in.is_open()) {
            std::cout << "Failed to open file: !" << absolutePathToTexts + file << std::endl;
        } else {
            std::stringstream buffer;
            buffer << in.rdbuf();
            std::string tempoWord;
            while (buffer >> tempoWord) {
                tempoWord = checker::checkWord(tempoWord);
                if (!tempoWord.empty()) {
                    checkedWords++;
                    if (!checker->check(tempoWord))
                        wrongWords++;
                }
            }
        }
    }
    auto endCheck = std::chrono::steady_clock::now();
    elapsed_seconds = endCheck - startCheck;
    std::cout
            << std::chrono::duration_cast<std::chrono::milliseconds>(elapsed_seconds).count() << " " << checkedWords
            << " " << wrongWords << std::endl;
}
