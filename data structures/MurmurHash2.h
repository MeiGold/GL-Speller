//
// Created by golde on 3/13/2020.
//

#ifndef SPELLER_MURMURHASH2_H
#define SPELLER_MURMURHASH2_H

#include <string>

template<class T>
class ChainNode {
private:
public:
    T value;
    ChainNode<T> *next;

    ChainNode() : value(nullptr), next(nullptr) {};

    ChainNode(T val) : value(val), next(nullptr) {};

    ChainNode(T val, ChainNode<T> *next) : value(val), next(next) {};
};


template<class T>
class MurmurHash2 {
private:
    int numberOfChains;
    ChainNode<T> **chains;

    unsigned int hashFunction(std::string element, unsigned int length);

public:
    MurmurHash2(int elementsCount);

    ~MurmurHash2();

    void insertElement(T element, unsigned int length);

    bool checkElement(T element, unsigned int length);

    int getMaxCollisions();
};


#include "MurmurHash2.cpp"

#endif //SPELLER_MURMURHASH2_H
