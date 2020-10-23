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

vector<distanceNode> approximate_nearest_neighbor(vector<unsigned char> qVec, vector < vector< vector <hTableNode> > > lHashTables, int L, int pos, int d, int N, ofstream &ofile);
vector<distanceNode> actual_nearest_neighbor(vector<unsigned char>  qVec, vector< vector< unsigned char> > pVec, int d, int N, ofstream &ofile);
vector<distanceNode> approximate_range_search(vector<unsigned char> qVec, vector < vector< vector <hTableNode> > > lHashTables, int L, int pos, int d, double R, ofstream &ofile);




#endif
