cmake_minimum_required(VERSION 3.15)
project(Speller)


list(APPEND SOURCES  "data structures/trie.cpp" src/sources/binaryTreeChecker.cpp src/sources/checker.cpp src/sources/hashTableChecker.cpp src/sources/main.cpp src/sources/trieChecker.cpp src/sources/unorderedMapChecker.cpp src/sources/vectorChecker.cpp)

set(CMAKE_CXX_CLANG_TIDY "clang-tidy;-header-filter=.*")
include_directories("data structures" include src/headers)
add_executable(Speller ${SOURCES})