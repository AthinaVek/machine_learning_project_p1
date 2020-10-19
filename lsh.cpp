#include "help_functions.h"
#include "calculations.h"

#include <algorithm>

#define m 536870912    // 2^29
#define NForTable 8

using namespace std;

// vector< list<HashTableNode> > *hashTable;


int main(int argc, char** argv){
	string iFile, qFile, oFile;
	int i, k, L, N;
	double R, w;
	int magic_number=0, number_of_images=0;
    int n_rows=0, n_cols=0;
    int d, M, h, pos;
    unsigned int g;
    int hTableSize;

	vector< vector<unsigned char> > pVec; 
	vector<unsigned char> tempVec;
	vector< vector<int> > sVec;
	vector<int> aVec;
	vector< vector<int> > hVec;
	vector<int> tempIntVec;
	vector< vector<unsigned char> > qVec;

	hTableNode node;
	
	read_input(&argc, argv, &iFile, &qFile, &k, &L, &oFile, &N, &R, &w);
	
	M = pow(2,(32/k));
	
	ifstream file (iFile);
    if (file.is_open()){
        
        read_data(file, &magic_number, &number_of_images, &n_rows, &n_cols, pVec, tempVec);
			
		d = n_rows * n_cols;						           // dimension
        hTableSize = number_of_images / NForTable;
        
        vector < vector< vector <hTableNode> > > lHashTables;       // vector with L hash tables
        vector< vector <hTableNode> > hashTable;       // hash table

		for (int l=0; l<L; l++){
	        for(int y=0; y<hTableSize; y++){
			    hashTable.push_back(vector<hTableNode>()); //initialize the first index with a 2D vector
			}

	        for (int i=0; i<k; i++){
				tempIntVec = get_s(w, d);                     //s_i uniform random generator
				sVec.push_back(tempIntVec);
				tempIntVec.erase(tempIntVec.begin(), tempIntVec.end());
	        }
	        
	        for (int i=0; i < number_of_images; i++){
				for (int j = 0; j < k; j++){
					aVec = calculate_a(pVec[i], sVec[j], w, d);  // calculate a for every image
					h = calculate_h(aVec, m, M, d);              // calculate h for every image
					tempIntVec.push_back(h);
				}
				hVec.push_back(tempIntVec);                      // save k*h of every image
	        	tempIntVec.erase(tempIntVec.begin(), tempIntVec.end());
	        	
	        	g = calculate_g(hVec[i], k);                  // calculate g for every image
	        	pos = g % hTableSize;                         // find the position to insert the image in the hash table

	        	node.pPos = i;
	        	node.g = g;
	        	node.pVec = pVec[i];
	        	hashTable[pos].push_back(node);            // insert image in the hash table
			}

			lHashTables.push_back(hashTable);
			hashTable.erase(hashTable.begin(), hashTable.end());
		}
		

		ifstream qfile (qFile);
	    if (qfile.is_open()){
	        
	        read_data(qfile, &magic_number, &number_of_images, &n_rows, &n_cols, qVec, tempVec);

	    	ofstream ofile (oFile);
			if (ofile.is_open()){
				for(int i = 0; i < 20; i++){
					
					for (int j = 0; j < k; j++){
						aVec = calculate_a(qVec[i], sVec[j], w, d);  // calculate a for every image
						h = calculate_h(aVec, m, M, d);              // calculate h for every image
						tempIntVec.push_back(h);
					}
					g = calculate_g(tempIntVec, k);                  // calculate g for every image
					pos = g % hTableSize;                         // find the position to insert the image in the hash table
					
					ofile  << "Query: " << i << endl;
					approximate_nearest_neighbor(qVec[i], lHashTables, L, pos, d, N, ofile);
					actual_nearest_neighbor(qVec[i], pVec, d, ofile);
					approximate_range_search( qVec[i], lHashTables, L, pos, d, R, ofile);
					ofile << endl;
				}
			}
		}
		else{
			cout << "Could not open query file." << endl;
		}
    }
    else {
    	cout << "Could not open input file." << endl;
    }
	return 0;
}
