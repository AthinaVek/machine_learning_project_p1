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

//~ class HashTableNode {    //private??
  //~ public:
  	//~ unsigned g;
  	//~ vector<unsigned char> pVec;
//~ };


//~ void insertToHashTable(vector< list<HashTableNode> > hashTable, int g, vector<unsigned char> vec, int hTableSize);


class HashTableNode{				//maybe new file
	
	unsigned int g;
	vector<unsigned char> pVec;
	
	//HashTableNode* next;
	
	public:
		
		HashTableNode();
		
		int get_g();
		
		void set_g(int g);
		
		void set_pVec(vector<unsigned char> pVec);
	
		virtual ~HashTableNode();
	
};

class HashTable{
	
	int size;
	vector<list<HashTableNode>> buckets;
	
	public:
		
		HashTable();
		
		HashTable(int size);
		
		int get_size();
		
		void insertToHashTable(int g, vector<unsigned char> pVec, int hTableSize);
		
		//void printHashTable();
		
		virtual ~HashTable();
	
	
	
};

#endif
