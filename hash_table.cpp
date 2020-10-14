#include "hash_table.h"


void insertToHashTable(vector<list<HashTableNode>> *hashTable, int g, vector<unsigned char> vec, int hTableSize){  
	int pos;
	HashTableNode node;

	pos = g % hTableSize;

	node.g = g;
	node.pVec.push_back(vec);

	hashTable[pos].push_back(node);
}