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
    int n_rows=0, n_cols=0, d, count=0;
    int k, L, kl, M, Ml, ky, probes, h; 
    int y, minc, changes = 6, first=1;
    unsigned int dist, g, min, x;
    double w, R;
    fNode fnode;
    bool exists;
    
	vector< vector<unsigned char> > pVec, centroids;
	vector<unsigned char> tempVec, pDim, tempC;
	vector< vector<int> > clusters, temp;
	vector< vector<int> > sVec;
	vector<int> aVec, tempIntVec, pos;
	vector< vector<distanceNode> > distRange;
	vector<distanceNode> distTemp;
	vector< vector<fNode> > fVec, cfVec;
	vector<fNode> tempfVec;
	
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
			while((count < 40) && (changes > 5)){
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
				count++;
			}
			cout << count << endl;
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

			create_hashtables_LSH(lHashTables, hashTable, pVec, L, hTableSize, kl, d, number_of_images, w, m, M);

			for (int i=0; i<kl; i++){
				tempIntVec = get_s(w, d);                     //s_i uniform random generator
				sVec.push_back(tempIntVec);
				tempIntVec.erase(tempIntVec.begin(), tempIntVec.end());
			}

			for (int i=0; i<k; i++){
				distRange.push_back(vector<distanceNode>());
			}

			for(int i=0; i<k; i++){                           //for every centroid
				for (int j=0; j<kl; j++){
					aVec = calculate_a(centroids[i], sVec[j], w, d);  // calculate a for every centroid
					h = calculate_h(aVec, m, Ml, d);              // calculate h for every centroid
					tempIntVec.push_back(h);
				}
				g = calculate_g(tempIntVec, kl);                  // calculate g for every centroid
				pos.push_back(g % hTableSize);                         // find the position to assign the centroid in the hash table
				tempIntVec.erase(tempIntVec.begin(), tempIntVec.end());
			}

			count = 0;
			while((count < 3) && (changes > 5)){
				changes = 0;
				for(int i=0; i<k; i++){                           //for every centroid
					distTemp = approximate_range_search_clusterLSH(centroids, lHashTables, L, pos[i], d, R, i);
					changes += distTemp.size();
					distRange[i].insert(distRange[i].end(), distTemp.begin(), distTemp.end() ); 
				}
				R = R*2;
				count++;
			}

			for(int i = 0; i < L; i++){															//for every hashtable
				for(int j = 0; j < lHashTables[i].size(); j++){									//for every bucket
					for(int y = 0; y < lHashTables[i][j].size(); y++){							//for every image in current bucket
						if (lHashTables[i][j][y].flag == 0){									//if not assigned to a centroid
							min = 4294967295;
							for(int c = 0; c < k; c++){											//find min distance from centroids
								x = manhattan_dist(pVec[lHashTables[i][j][y].pPos], centroids[c], d);
								if (x < min){
									min = x;
									minc = c;
								}
							}
							lHashTables[i][j][y].flag = 1;
							lHashTables[i][j][y].cluster = minc;
						}
					}
				}
			}
		}

		else if(method == "Hypercube"){
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

			create_hashtable_cube(hashTable, pVec, sVec, hTableSize, number_of_images, w, ky, d, m, M);

			for (int i=0; i<k; i++){
				distRange.push_back(vector<distanceNode>());
			}

			for(int i=0; i<k; i++){
				for(int j=0; j<ky; j++){                           //for every centroid
					aVec = calculate_a(centroids[i], sVec[j], w, d);  // calculate a for every centroid
					h = calculate_h(aVec, m, Ml, d);              // calculate h for every centroid

					exists = 0;
					for (int y=0; y<tempfVec.size(); y++){
						if (h == tempfVec[y].h){
							exists = 1;
							fnode.h = h;
							fnode.f = tempfVec[y].f;
							break;
						}
					}
					if(exists == 0){
						for (int j=0; j<cfVec.size(); j++){
							for (int p=0; p<cfVec[j].size(); p++){
								if (h == cfVec[j][p].h){
									exists = 1;
									fnode.h = h;
									fnode.f = cfVec[j][p].f;
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
						fnode.f = get_f();
					}
					tempfVec.push_back(fnode);
				}

				cfVec.push_back(tempfVec);                    		  // save f*k distinct of every image
				tempfVec.erase(tempfVec.begin(), tempfVec.end());
				
				pos[i] = calculate_p(cfVec[i], ky);
			}

			count = 0;
			while((count < 3) && (changes > 5)){
			// 	changes = 0;
			// 	for(int i=0; i<k; i++){
			// 		distRange = approximate_range_search_cube(centroids, hashTable, pos[i], d, R, M, probes);
			// 		changes += distTemp.size();
			// 		distRange[i].insert(distRange[i].end(), distTemp.begin(), distTemp.end() ); 
			// 	}
				
			
				// 		// for (int y=0; y<distRange[i].size(); y++){
				// 		// 	cout << distRange[i][y].pPos << endl;
				// 		// cout << distRange[i].size() << endl;
				// 		// cout << "===============" << endl;

				R = R*2;
				count++;
			}
			
			
		}
		else{
			cout << "This method does not exist..." << endl;
		}
	}
	return 0;
}
