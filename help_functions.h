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


using namespace std;

int reverseInt (int i);

void read_input(int* argc, char** argv, string* iFile, string* qFile, int* k, int* L, string* oFile, int* N, double* R, double* w);
void read_data(ifstream &file, int* magic_number, int* number_of_images, int* n_rows, int* n_cols, vector< vector<unsigned char> >& pVec, vector<unsigned char>& tempVec);

// void printNestedList(list<list<unsigned char> > nested_list);


#endif
