#ifndef __CALCULATIONS_H__
#define __CALCULATIONS_H__

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

using namespace std;

class hTableNode{
public:
	int pPos;
	unsigned int g;
	vector<unsigned char> pVec;
};

class distanceNode{
public:
	int pPos;
	unsigned int dist;
};

vector<int> get_s(double w, int d);
vector<int> calculate_a(vector<unsigned char> pVec, vector<int> sVec, double w, int d);
int calculate_h(vector<int> aVec, int m, int M, int d);
unsigned int calculate_g(vector<int> hVec, int k);
unsigned int manhattan_dist(vector<unsigned char> qVec, vector<unsigned char> pVec, int d);

void approximate_nearest_neighbor(vector<unsigned char> qVec, vector < vector< vector <hTableNode> > > lHashTables, int L, int pos, int d, int N, ofstream &ofile);
// unsigned int actual_nearest_neighbor(vector<unsigned char>  qVec, vector< vector< unsigned char> > pVec, int d);
// void approximate_range_search(vector<unsigned char> qVec, vector < vector< vector <vector<unsigned char> > > > lHashTables, int L, int pos, int d, double R, ofstream &ofile);

#endif
