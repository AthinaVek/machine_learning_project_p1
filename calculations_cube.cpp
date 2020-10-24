#include "calculations_cube.h"

unsigned int calculate_p(vector<fNode> fVec, int k){
	unsigned int p=0;

	for (int i=0; i<k; i++){
		p = fVec[i].f << (k-1-i) | p ;
	}
	// cout << "///" << p << endl;
	// p = (int)p | (int)pow(2,k);
	// cout << p << endl;
	return p;
}


vector<int> hamming_dist(int probes, int p){
	vector<int> hp;
	int x, count, mask;


	for (int i=0; i<probes; i++){
		mask = 1 << i;
		if (p & mask){
			x = (p & ~mask) | ((0 << i) & mask);
		}
		else{
			x = (p & ~mask) | ((1 << i) & mask);
		}
		hp.push_back(x);
	}
	return hp;
}


vector<distanceNode> approximate_nearest_neighbor_cube(vector<unsigned char> qVec, vector< vector <hTableNode> > hashTable, int p, int d, int N, int M, int probes, ofstream &ofile){
	unsigned int temp;
	distanceNode node;
	vector<distanceNode> distances;
	vector<int> ph;
	int count=0;
	
	ph = hamming_dist(probes-1, p);                           // Find positions with Hamming distance 1
	ph.insert(ph.begin(), p);                                 // Put p position in position 0 to search first

	for(int i = 0; i < N; i++){
		node.pPos = -1;
		node.dist = 4294967295;                        //highest possible unsigned int
		distances.push_back(node);	
	}
	
	for(int i=0; i<ph.size(); i++){                           // For every position with Hamming distance 1 until it searches M images
		for(int j=0; j < hashTable[ph[i]].size(); j++){
			temp = manhattan_dist(qVec, hashTable[ph[i]][j].pVec, d);
			cout << "temp   " << temp << endl;
			if(temp < distances[N-1].dist){
				cout << " in " << endl;
				cout << "in for   " << endl;
				distances[N-1].dist = temp;
				distances[N-1].pPos = hashTable[ph[i]][j].pPos;
				for(int c=N-2; c>=0; c--){
					if(distances[c].dist > distances[c+1].dist){
						iter_swap(distances.begin() + c, distances.begin() + c+1);
					}
					else{
						break;
					}
				}
			}
			count++;
			if (count >= M){
				break;
			}
		}
		if (count >= M){
			break;
		}
	}
	return distances;
 }


vector<distanceNode> approximate_range_search_cube(vector<unsigned char> qVec, vector< vector <hTableNode> > hashTable, int p, int d, double R, ofstream &ofile, int M, int probes){
	unsigned int temp;
	vector<distanceNode> distances;
	vector<int> ph;
	distanceNode node;
	int count=0;
	
	ph = hamming_dist(probes-1, p);                           // Find positions with Hamming distance 1
	ph.insert(ph.begin(), p);                                 // Put p position in position 0 to search first

	for(int i=0; i<ph.size(); i++){                           // For every position with Hamming distance 1 until it searches M images
		// cout << "hhhhhhhhhhh" << hashTable[ph[i]].size() << endl;
		for(int j=0; j < hashTable[ph[i]].size(); j++){
			temp = manhattan_dist(qVec, hashTable[ph[i]][j].pVec, d);
			// cout << temp << endl;
			if(temp < R){
				node.pPos = hashTable[ph[i]][j].pPos;
				node.dist = temp;
				distances.push_back(node);
				// cout << "----" << hashTable[ph[i]][j].pPos << endl;
			}
			count++;
			if (count >= M){
				break;
			}
		}
		if (count >= M){
			break;
		}
	}
	// cout << count << endl;

	return distances;
}
