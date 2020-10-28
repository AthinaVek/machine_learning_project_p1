#ifndef __CALCULATIONS_CLUSTER_H__
#define __CALCULATIONS_CLUSTER_H__

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


void k_means_init(vector< vector<unsigned char> > &centroids, int number_of_images, vector< vector<unsigned char> > pVec, int k, int d);

void lloyds_assignment(vector< vector<int> > &clusters, vector< vector<int> > temp, int number_of_images, vector< vector<unsigned char> > pVec, vector< vector<unsigned char> > centroids, int k, int d, int *changes, int first);

#endif
