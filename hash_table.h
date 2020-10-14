#ifndef __HASH_TABLE_H__
#define __HASH_TABLE_H__

#include <iostream>
#include <cstdlib>
#include <fstream>
#include <bits/stdc++.h>
#include <string>
#include <list> 
#include <iterator> 
#include <random>
#include <vector>
#include <cmath>

using namespace std;

class HashTableNode {    //private??
  public:
  	unsigned g;
  	vector<unsigned char> pVec;
};


void insertToHashTable(vector< list<HashTableNode> > hashTable, int g, vector<unsigned char> vec, int hTableSize);

#endif