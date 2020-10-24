#include "help_functions.h"
#include "calculations.h"
#include "calculations_cube.h"

#define m 107					//a_max < m < M/2
#define NForTable 16

using namespace std;


int main(int argc, char** argv){
	string iFile, qFile, oFile;
	int i, k, probes, N;
	double R, w;
	int magic_number=0, number_of_images=0;
    int n_rows=0, n_cols=0;
    int d, M, h, pos, p;
    unsigned int g;
    int hTableSize;
    bool exists;

	vector< vector<unsigned char> > pVec, qVec; 
	vector<unsigned char> tempVec;
	vector< vector<int> > sVec;
	vector<int> aVec, tempIntVec;
	vector<fNode> tempfVec;
	vector< vector<fNode> > fVec, qfVec;
	vector<distanceNode> distCube, distTrue, distRange;

	hTableNode node;
	fNode fnode;
	
	read_inputCube(&argc, argv, &iFile, &qFile, &k, &M, &probes, &oFile, &N, &R, &w);
	
	srand (time(NULL));
	
	ifstream file (iFile);
    if (file.is_open()){
	    read_data(file, &magic_number, &number_of_images, &n_rows, &n_cols, pVec, tempVec);
			
		d = n_rows * n_cols;						           // dimension
	    hTableSize = pow(2,k);
	    
	    vector< vector <hTableNode> > hashTable;       // hash table

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

				exists = 0;
				
				for (int p=0; p<tempfVec.size(); p++){
					if (h == tempfVec[p].h){
						exists = 1;
						fnode.h = h;
						fnode.f = tempfVec[p].f;
						break;
					}
				}
				
				if(exists == 0){
					for (int j=0; j<fVec.size(); j++){
						for (int p=0; p<fVec[j].size(); p++){
							if (h == fVec[j][p].h){
								exists = 1;
								fnode.h = h;
								fnode.f = fVec[j][p].f;
								break;
							}
						}
						if (exists){
							break;
						}
					}
				}
				
				if (exists == 0){
					fnode.h = h;
					fnode.f = rand() % 2 + 0;
				}
				tempfVec.push_back(fnode);
				// cout << fnode.f << endl;
			}

			fVec.push_back(tempfVec);                      // save f*k distinct of every image
        	tempfVec.erase(tempfVec.begin(), tempfVec.end());
        	
        	p = calculate_p(fVec[i], k);

        	// bitset<32> x(p);
        	// cout << "p:  " << x << endl << endl;

        	// cout << "p:  " << p << endl;

			node.pPos = i;
        	node.pVec = pVec[i];
        	hashTable[p].push_back(node);            // insert image in the hash table

        	// cout << "!!!!" << endl;

		}


		ifstream qfile (qFile);
		if (qfile.is_open()){
			read_data(qfile, &magic_number, &number_of_images, &n_rows, &n_cols, qVec, tempVec);

			ofstream ofile (oFile);
			if (ofile.is_open()){
				for(int i = 0; i < number_of_images; i++){
				
					for (int j = 0; j < k; j++){
						aVec = calculate_a(qVec[i], sVec[j], w, d);  // calculate a for every image
						h = calculate_h(aVec, m, M, d);              // calculate h for every image
						tempIntVec.push_back(h);
					
						exists = 0;
				
						for (int p=0; p<tempfVec.size(); p++){
							if (h == tempfVec[p].h){
								exists = 1;
								fnode.h = h;
								fnode.f = tempfVec[p].f;
								break;
							}
						}
						
						if(exists == 0){
							for (int j=0; j<qfVec.size(); j++){
								for (int p=0; p<qfVec[j].size(); p++){
									if (h == qfVec[j][p].h){
										exists = 1;
										fnode.h = h;
										fnode.f = qfVec[j][p].f;
										break;
									}
								}
								if (exists){
									break;
								}
							}
						}
						
						if (exists == 0){
							fnode.h = h;
							fnode.f = rand() % 2 + 0;
						}
						tempfVec.push_back(fnode);
					}
					
					qfVec.push_back(tempfVec);                    		  // save f*k distinct of every image
					tempfVec.erase(tempfVec.begin(), tempfVec.end());
					
					p = calculate_p(qfVec[i], k);
					
					auto t1 = chrono::high_resolution_clock::now();
					distCube = approximate_nearest_neighbor_cube(qVec[i], hashTable, p, d, N, M, probes, ofile);
					auto t2 = chrono::high_resolution_clock::now();
					auto durationCube = chrono::duration_cast<chrono::microseconds>( t2 - t1 ).count();

					auto t3 = chrono::high_resolution_clock::now();
					distTrue = actual_nearest_neighbor(qVec[i], pVec, d, N, ofile);
					auto t4 = chrono::high_resolution_clock::now();
					auto durationTrue = chrono::duration_cast<chrono::microseconds>( t4 - t3 ).count();

					distRange = approximate_range_search_cube(qVec[i], hashTable, p, d, R, ofile, M, probes);

					ofile  << "Query: " << i << endl;               // write to file
					for (int j=0; j<N; j++){
						ofile << "Nearest neighbor-N: " << distCube[j].pPos << endl;
						ofile << "distanceHyperCube: " << distCube[j].dist << endl;
						ofile << "distanceTrue: " << distTrue[j].dist << endl;
					}
					ofile << "tHyperCube: " << durationCube << endl;
					ofile << "tTrue: " << durationTrue << endl;
					ofile << "R-near neighbors:" << endl;
					if (distRange.size() == 0){
						ofile << "No neighbors in this range." << endl;
					}
					else{
						for(int c=0; c<distRange.size(); c++){
							ofile << distRange[c].pPos << endl;
						}
					}
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
