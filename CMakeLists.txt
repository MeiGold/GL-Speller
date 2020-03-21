cmake_minimum_required(VERSION 3.15)
project(Speller)

set(CMAKE_CXX_CLANG_TIDY "clang-tidy;-checks=*")
include_directories("data structures" checkers)
add_executable(Speller main.cpp checkers/checker.cpp checkers/vectorChecker.cpp checkers/binaryTreeChecker.cpp checkers/hashTableChecker.cpp checkers/unorderedMapChecker.cpp checkers/trieChecker.cpp "data structures/trie.cpp")