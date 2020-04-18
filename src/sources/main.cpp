#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <dirent.h>
#include <sstream>
#include <chrono>
#include <cstring>

#include "vectorChecker.h"
#include "binaryTreeChecker.h"
#include "hashTableChecker.h"
#include "unorderedMapChecker.h"
#include "trieChecker.h"

namespace {
    // variables for dictionary, input and output
    const char *dictionaryPath = "../dictionary.txt";
    const char *absolutePathToOutputs = "../outputs/";
    const char *absolutePathToTexts = "../texts/";
    //
}

using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::vector;

vector<string> loadDictionary(const char *dictionaryPath);

vector<vector<string>> readFiles(const vector<string> &filePaths);

void checkFiles(const vector<string> &fileNames, const vector<vector<string>> &files,
                checker *checker, const string &output, const vector<string> &dictionary);

int main() {
    cout << "------------------------Speller------------------------" << endl;
    vector<string> files;
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
    vector<vector<string>> filesContainer = readFiles(
            files);//vector of vectors containing words from given files
    vector<string> dictionary = loadDictionary(dictionaryPath);

    checker *c;
    c = new vectorChecker();
    checkFiles(files, filesContainer, c, "stdvector", dictionary);
    delete c;

    c = new binaryTreeChecker();
    checkFiles(files, filesContainer, c, "BST", dictionary);
    delete c;

    c = new hashTableChecker(1947827);//it can be any approximate size
    checkFiles(files, filesContainer, c, "hashTable", dictionary);
    delete c;

    c = new unorderedMapChecker();
    checkFiles(files, filesContainer, c, "unorderedHashMap", dictionary);
    delete c;

    c = new trieChecker();
    checkFiles(files, filesContainer, c, "trie", dictionary);
    delete c;
    return 0;
}

vector<string> loadDictionary(const char *dictionaryPath) {
    vector<string> dict;
    std::ifstream in(dictionaryPath);
    if (!in.is_open()) {
        cout << "Failed to open dictionary!" << endl;
    } else {
        std::stringstream buffer;
        buffer << in.rdbuf();
        string tempoWord;
        while (buffer >> tempoWord) {
            tempoWord = checker::checkWord(tempoWord);
            if (!tempoWord.empty()) { dict.emplace_back(tempoWord); }
        }
    }
    return dict;
}

vector<vector<string>> readFiles(const vector<string> &filePaths) {
    vector<vector<string>> files;
    for (const auto &file : filePaths) {
        vector<string> tempoFile;
        std::ifstream in(absolutePathToTexts + file);
        if (!in.is_open()) {
            cout << "Failed to open file: !" << absolutePathToTexts + file << endl;
        } else {
            std::stringstream buffer;
            buffer << in.rdbuf();
            string tempoWord;
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


void checkFiles(const vector<string> &fileNames, const vector<vector<string>> &files,
                checker *const checker, const string &output, const vector<string> &dictionary) {
    cout << output << " ";
    auto start = std::chrono::steady_clock::now();
    checker->createDictionary(dictionary);
    auto end = std::chrono::steady_clock::now();
    std::chrono::duration<double> elapsed_seconds = end - start;
    cout
            << std::chrono::duration_cast<std::chrono::milliseconds>(elapsed_seconds).count() << " ";
    auto startCheck = std::chrono::steady_clock::now();
    int checkedWords = 0;
    int wrongWords = 0;
    for (const auto &file : files) {
        for (const auto &word : file) {
            checkedWords++;
            if (!checker->check(word)) {
                wrongWords++;
            }
        }
    }
    auto endCheck = std::chrono::steady_clock::now();

    for (int i = 0; i < files.size(); ++i) {
        std::ofstream of(absolutePathToOutputs + output + "/" + fileNames[i]);
        for (const auto &word : files[i]) {
            if (!checker->check(word)) {
                of << word << '\n';
            }
        }
    }
    elapsed_seconds = endCheck - startCheck;
    cout
            << std::chrono::duration_cast<std::chrono::milliseconds>(elapsed_seconds).count() << " " << checkedWords
            << " " << wrongWords << endl;
}

