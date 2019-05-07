#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <string>
#include <list>
#include <iostream>
#include "WordEntry.h"

using namespace std;

class HashTable {

    private:
        list<WordEntry> *hashTable;
        int computeHash(string);
        int size;

    public:
        HashTable(int);
        bool contains(string);
        double getAverage(string);
        void put(string,int);
        void displayHash(); //test
};

#endif
