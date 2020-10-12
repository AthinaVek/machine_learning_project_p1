#ifndef __HELP_FUNCTIONS_H__
#define __HELP_FUNCTIONS_H__

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

int reverseInt (int i);

vector<double> get_s(double w, int d);
vector<int> calculate_a(vector<unsigned char> pVec, vector<double> sVec, double w, int d);
int calculate_h(vector<int> aVec, int m, int M, int d);

// void printNestedList(list<list<unsigned char> > nested_list);


#endif
