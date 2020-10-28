#include "help_functions.h"
#include "calculations.h"
#include "calculations_lsh.h"
#include "calculations_cube.h"
#include "calculations_cluster.h"

#define m 107					//a_max < m < M/2
#define NForTable 16

using namespace std;


int main(int argc, char** argv){
	string iFile, confFile, oFile, method;
	int magic_number=0, number_of_images=0, hTableSize;
    int n_rows=0, n_cols=0, d;
    int k, L, kl, M, Ml, ky, probes, pos, h; 
    int y, minc, changes = 6, first=1;
    unsigned int dist, g, min, x;
    double w, R;
    hTableNode node;
    
	vector< vector<unsigned char> > pVec, centroids;
	vector<unsigned char> tempVec, pDim, tempC;
	vector< vector<int> > clusters, temp;
	vector< vector<int> > sVec, hVec;
	vector < vector< vector<int> > > lsVecs;
	vector<int> aVec, tempIntVec;
	
	srand (time(NULL));

	read_inputCluster(&argc, argv, &iFile, &confFile, &oFile, &method);
	read_confFile(&k, &L, &kl, &M, &ky, &probes, confFile);

	Ml = pow(2,floor(32/kl));
	
	ifstream file (iFile);
	if (file.is_open()){
		read_data(file, &magic_number, &number_of_images, &n_rows, &n_cols, pVec, tempVec);

		for(int i = 0; i < k; i++){
			clusters.push_back(vector<int>());
			temp.push_back(vector<int>());
		} 
		
		d = n_rows * n_cols;
		hTableSize = number_of_images / NForTable;
		
		k_means_init(centroids, number_of_images, pVec, k, d);
		
		if(method == "Classic"){
			while(changes > 5){
				changes = 0;

				lloyds_assignment(clusters, temp, number_of_images, pVec, centroids, k, d, &changes, first);
				
				if(!first){
					if (changes <= 5)
						break;
				}
				else{
					changes = 6;
				}	
				
				// new centroids
				centroids.erase(centroids.begin(), centroids.end());
				
				update_centroids_median(centroids, pDim, pVec, clusters, tempC, k, d);
				
				first = 0;
			}
		}

		else if(method == "LSH"){
			vector < vector< vector <hTableNode> > > lHashTables;       // vector with L hash tables
			vector< vector <hTableNode> > hashTable;       // hash table
			
			min = 4294967295;
			for (int i=0; i<k; i++){
				for (int j=0; j<k; j++){
					if (i != j){
						x = manhattan_dist(centroids[i], centroids[j], d);
						if (x < min){
							min = x;
						}
					}
				}
			}

			R = min/2;
			w = 4*R;

			create_hashtables_LSH(lHashTables, hashTable, pVec, sVec, lsVecs, aVec, hVec, node, L, hTableSize, kl, d, number_of_images, w, m, M);

			for (int i=0; i<kl; i++){
				tempIntVec = get_s(w, d);                     //s_i uniform random generator
				sVec.push_back(tempIntVec);
				tempIntVec.erase(tempIntVec.begin(), tempIntVec.end());
			}

			for(int i=0; i<k; i++){                           //for every centroid
				for (int j=0; j<kl; j++){
					aVec = calculate_a(centroids[i], sVec[j], w, d);  // calculate a for every centroid
					h = calculate_h(aVec, m, Ml, d);              // calculate h for every centroid
					// cout << h << endl;
					tempIntVec.push_back(h);
				}
				g = calculate_g(tempIntVec, kl);                  // calculate g for every centroid
				pos = g % hTableSize;                         // find the position to assign the centroid in the hash table
				
				cout << pos << endl;
			}
		}

		else if(method == "Hypercube"){
			
			
			
		}
		else{
			cout << "This method does not exist..." << endl;
		}
	}
	return 0;
}
