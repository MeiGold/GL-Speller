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

std::vector<std::vector<std::string>> readFiles(const std::vector<std::string> &filePaths);

void checkFiles(const std::vector<std::string> &fileNames, const std::vector<std::vector<std::string>> &files,
                checker *checker, const std::string &output);

int main() {
    std::cout << "------------------------Speller------------------------" << std::endl;
    std::vector<std::string> files;
    DIR *dir;
    struct dirent *ent;
    if ((dir = opendir(absolutePathToTexts)) != nullptr) {
        /* print all the files and directories within directory */
        while ((ent = readdir(dir)) != nullptr) {
            if (strncmp(ent->d_name, ".", 2) != 0 && strncmp(ent->d_name, "..", 3) != 0) {
                files.emplace_back(ent->d_name);
            }
        }
        closedir(dir);
    } else {
        /* could not open directory */
        perror("");
        return EXIT_FAILURE;
    }
    std::vector<std::vector<std::string>> filesContainer = readFiles(files);

    checker *c;
    c = new vectorChecker();
    checkFiles(files, filesContainer, c, "stdvector");

    c = new binaryTreeChecker();
    checkFiles(files, filesContainer, c, "BST");

    c = new hashTableChecker(1947827);//it can be any approximate size
    checkFiles(files, filesContainer, c, "hashTable");

    c = new unorderedMapChecker();
    checkFiles(files, filesContainer, c, "unorderedHashMap");

    c = new trieChecker();
    checkFiles(files, filesContainer, c, "trie");
    return 0;
}

std::vector<std::vector<std::string>> readFiles(const std::vector<std::string> &filePaths) {
    std::vector<std::vector<std::string>> files;
    for (const auto &file : filePaths) {
        std::vector<std::string> tempoFile;
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
                    tempoFile.emplace_back(tempoWord);
                }
            }
        }
        files.emplace_back(tempoFile);
    }
    return files;
}

void checkFiles(const std::vector<std::string> &fileNames, const std::vector<std::vector<std::string>> &files,
                checker *const checker, const std::string &output) {
    std::cout << output << " ";
    auto start = std::chrono::steady_clock::now();
    checker->createDictionary(dictionaryPath);
    auto end = std::chrono::steady_clock::now();
    std::chrono::duration<double> elapsed_seconds = end - start;
    std::cout
            << std::chrono::duration_cast<std::chrono::milliseconds>(elapsed_seconds).count() << " ";
    auto startCheck = std::chrono::steady_clock::now();
    int checkedWords = 0;
    int wrongWords = 0;
    for (int i = 0; i < files.size(); ++i) {
        std::ofstream of(absolutePathToOutputs + output + "/" + fileNames[i]);
        for (const auto &word:files[i]) {
            if (word == "which") {
                int a = 5;
            }
            checkedWords++;
            if (!checker->check(word)) {
                wrongWords++;
                of << word << '\n';
            }
        }
    }
    auto endCheck = std::chrono::steady_clock::now();
    elapsed_seconds = endCheck - startCheck;
    std::cout
            << std::chrono::duration_cast<std::chrono::milliseconds>(elapsed_seconds).count() << " " << checkedWords
            << " " << wrongWords << std::endl;
}

