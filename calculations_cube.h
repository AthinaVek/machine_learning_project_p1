#ifndef __CALCULATIONS_CUBE_H__
#define __CALCULATIONS_CUBE_H__

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


class fNode{
public:
	int h;
	bool f;
};

unsigned int calculate_p(vector<fNode> fVec, int k);
vector<int> hamming_dist(int probes, int p);

int get_f();

vector<distanceNode> approximate_nearest_neighbor_cube(vector<unsigned char> qVec, vector< vector <hTableNode> > hashTable, int p, int d, int N, int M, int probes, ofstream &ofile);
vector<distanceNode> approximate_range_search_cube(vector<unsigned char> qVec, vector< vector <hTableNode> > hashTable, int p, int d, double R, ofstream &ofile, int M, int probes);


#endif
