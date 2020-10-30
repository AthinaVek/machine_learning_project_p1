#ifndef __CALCULATIONS_LSH_H__
#define __CALCULATIONS_LSH_H__

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
#include <vector>
#include <chrono>
#include <algorithm>
#include <climits>

#include "calculations.h"

using namespace std;


unsigned int calculate_g(vector<int> hVec, int k);

void create_hashtables_LSH(vector < vector< vector <hTableNode> > > &lHashTables, vector< vector <hTableNode> > &hashTable, vector< vector<unsigned char> > pVec, vector< vector<int> > sVec, vector<int> aVec, vector< vector<int> > hVec, hTableNode node, int L, int hTableSize, int k, int d, int number_of_images, double w, int m, int M);

vector<distanceNode> approximate_nearest_neighbor(vector<unsigned char> qVec, vector < vector< vector <hTableNode> > > lHashTables, int L, int pos, int d, int N);
vector<distanceNode> approximate_range_search(vector<unsigned char> qVec, vector < vector< vector <hTableNode> > > lHashTables, int L, int pos, int d, double R);

#endif
