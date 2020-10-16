#include "hash_table.h"


//~ void insertToHashTable(vector<list<HashTableNode>> *hashTable, int g, vector<unsigned char> vec, int hTableSize){  
	//~ int pos;
	//~ HashTableNode node;

	//~ pos = g % hTableSize;

	//~ node.g = g;
	//~ node.pVec.push_back(vec);

	//~ hashTable[pos].push_back(node);
//~ }


HashTable::HashTable(){
	cout << "Created hash table" << endl;
}


HashTable::HashTable(int size) : size(size){
	cout << "Created hash table with size: " << get_size() << endl;
}


int HashTable::get_size(){
	return size;
}


//~ void HashTable::insertToHashTable(int g, vector<unsigned char> pVec, int hTableSize){
	//~ int pos;
	
	//~ HashTableNode node;

	//~ pos = g % hTableSize;

	//~ node.set_g(g);
	//~ node.set_pVec(pVec);
	
	//~ buckets[pos].push_back(node);
//~ }

HashTable::~HashTable(){
	cout << "Hash table destroyed!" << endl;
}






HashTableNode::HashTableNode(){
	cout << "Created new node for hash table!" << endl;
}


int HashTableNode::get_g(){
	return g;
}

void HashTableNode::set_g(int g){
	this->g = g;
}

void HashTableNode::set_pVec(vector<unsigned char> pVec){
	this->pVec = pVec;
}

HashTableNode::~HashTableNode(){
	cout << "Destroyed node from hash table!" << endl;
}







