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
#include <chrono>
#include <algorithm>
#include <climits>

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

int modular_pow(int base, int exponent, int modulus);

vector<int> get_s(double w, int d);
vector<int> calculate_a(vector<unsigned char> pVec, vector<int> sVec, double w, int d);
int calculate_h(vector<int> aVec, int m, int M, int d);
unsigned int manhattan_dist(vector<unsigned char> qVec, vector<unsigned char> pVec, int d);



#endif
