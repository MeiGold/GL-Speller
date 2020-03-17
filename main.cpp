#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <dirent.h>
#include <sstream>
#include <chrono>
#include <cstring>

#include <checker.h>
#include <vectorChecker.h>
#include <binaryTreeChecker.h>
#include <hashTableChecker.h>
#include <unorderedMapChecker.h>
#include <trieChecker.h>

namespace {
    // variables for dictionary, input and output
    const char *dictionaryPath = "../dictionary.txt";
    const char *absolutePathToOutputs = "../outputs/";
    const char *absolutePathToTexts = "../texts/";
}

void checkFiles(const std::vector<std::string> &files, checker *checker, const std::string &output);

int main() {
    std::vector<std::string> files;
    DIR *dir;
    struct dirent *ent;
    if ((dir = opendir(absolutePathToTexts)) != nullptr) {
        /* print all the files and directories within directory */
        while ((ent = readdir(dir)) != nullptr) {
            if (strncmp(ent->d_name, ".", 2) != 0 && strncmp(ent->d_name, "..", 3) != 0)
                files.emplace_back(ent->d_name);
        }
        closedir(dir);
    } else {
        /* could not open directory */
        perror("");
        return EXIT_FAILURE;
    }
    std::cout << "------------------------Speller------------------------" << std::endl;

    checker *c;
    c = new vectorChecker();
    std::cout << "stdvector ";
    checkFiles(files, c, std::string(absolutePathToOutputs) + "stdvector\\");

    c = new binaryTreeChecker();
    std::cout << "BST ";
    checkFiles(files, c, std::string(absolutePathToOutputs) + "BST\\");

    c = new hashTableChecker(2000000);
    std::cout << "hashTable ";
    checkFiles(files, c, std::string(absolutePathToOutputs) + "hashTable\\");

    c = new unorderedMapChecker();
    std::cout << "unorderedHashMap ";
    checkFiles(files, c, std::string(absolutePathToOutputs) + "unorderedHashMap\\");

    c = new trieChecker();
    std::cout << "trie ";
    checkFiles(files, c, std::string(absolutePathToOutputs) + "trie\\");
    return 0;
}

void checkFiles(const std::vector<std::string> &files, checker *const checker, const std::string &output) {
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
        std::ofstream of(output + file);
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
                    if (!checker->check(tempoWord)) {
                        wrongWords++;
                        of << tempoWord << '\n';
                    }
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

