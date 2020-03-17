//
// Created by golde on 3/13/2020.
//

#include "MurmurHash2.h"


template<class T>
MurmurHash2<T>::MurmurHash2(int elementsCount) {
    numberOfChains = elementsCount / 5; // optimal number of chains
    chains = new ChainNode<T> *[numberOfChains];
}

template<class T>
unsigned int MurmurHash2<T>::hashFunction(std::string element, unsigned int length) {

    const unsigned int m = 0x5bd1e995;
    const unsigned int seed = 0;
    const int r = 24;

    unsigned int h = seed ^length;

    //const auto *data = (const unsigned char *) element;
    const unsigned char *data = reinterpret_cast<const unsigned char *> (element.c_str());
    unsigned int k;

    while (length >= 4) {
        k = data[0];
        k |= data[1] << 8;
        k |= data[2] << 16;
        k |= data[3] << 24;

        k *= m;
        k ^= k >> r;
        k *= m;

        h *= m;
        h ^= k;

        data += 4;
        length -= 4;
    }

    switch (length) {
        case 3:
            h ^= data[2] << 16;
        case 2:
            h ^= data[1] << 8;
        case 1:
            h ^= data[0];
            h *= m;
    };

    h ^= h >> 13;
    h *= m;
    h ^= h >> 15;

    return h % numberOfChains;
}

template<class T>
void MurmurHash2<T>::insertElement(T element, unsigned int length) {
    int index = hashFunction(element, length);
    chains[index] = new ChainNode<T>(element, chains[index]);
}

template<class T>
bool MurmurHash2<T>::checkElement(T element, unsigned int length) {
    int index = hashFunction(element, length);
    for (ChainNode<T> *x = chains[index]; x != nullptr; x = x->next) {
        if (x->value == element) return true;
    }
    return false;
}

template<class T>
int MurmurHash2<T>::getMaxCollisions() {
    unsigned int max = 0;
    for (int i = 0; i < numberOfChains; ++i) {
        if (chains[i]) {
            ChainNode<T> *currentNode = chains[i];
            int currentChainLength = 1;
            while (currentNode->next != nullptr) {
                currentChainLength++;
                currentNode = currentNode->next;
            }
            if (currentChainLength > max)max = currentChainLength;
        }

    }
    return max;
}

template<class T>
MurmurHash2<T>::~MurmurHash2() {
    delete[]chains;
}

