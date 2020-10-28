#include "help_functions.h"
#include "calculations.h"
#include "calculations_lsh.h"
#include "calculations_cube.h"
#include "calculations_cluster.h"

using namespace std;


int main(int argc, char** argv){
	string iFile, confFile, oFile, method;
	int magic_number=0, number_of_images=0;
    int n_rows=0, n_cols=0, d;
    int k, L, kl, M, ky, probes, median; 
    int y, minc, changes = 6, first=1;
    unsigned int dist;
    float x, max = 0, min;
    double cSize;
    
    
	vector< vector<unsigned char> > pVec; 
	vector<unsigned char> tempVec;
	vector< vector<unsigned char> > centroids;
	vector< vector<int> > clusters;
	vector< vector<int> > temp;
	
	srand (time(NULL));
	
	read_inputCluster(&argc, argv, &iFile, &confFile, &oFile, &method);
	read_confFile(&k, &L, &kl, &M, &ky, &probes, confFile);
	
	ifstream file (iFile);
	if (file.is_open()){
		read_data(file, &magic_number, &number_of_images, &n_rows, &n_cols, pVec, tempVec);

		for(int i = 0; i < k; i++){
			clusters.push_back(vector<int>());
			temp.push_back(vector<int>());
		} 
		
		d = n_rows * n_cols;
		
		k_means_init(centroids, number_of_images, pVec, k, d);
		
		if(method == "Classic"){
			while(changes > 5){
				changes = 0;

				lloyds_assignment(clusters, temp, number_of_images, pVec, centroids, k, d, &changes, first);
				
				if(!first){
					if (changes <= 5)
						break;
				}
					
				// new centroids
				centroids.erase(centroids.begin(), centroids.end());
				vector <unsigned char> pDim, tempC;
				
				for (int j=0; j<k; j++){											//for every cluster
					for (int z=0; z<d; z++){										//for every dimension
						for (int i=0; i<clusters[j].size(); i++){					//for every image in the cluster
							pDim.push_back(pVec[clusters[j][i]][z]);
						}
						
						quicksort(pDim, 0, pDim.size() - 1);
						
						cSize = (double)pDim.size();
						median = ceil(cSize/2);										//median
						tempC.push_back(pDim[median]);

						pDim.erase(pDim.begin(), pDim.end());
					}
					centroids.push_back(tempC);
					tempC.erase(tempC.begin(), tempC.end());
				}
				first = 0;
			}
		}
		else if(method == "LSH"){
			
			vector < vector< vector <hTableNode> > > lHashTables;       // vector with L hash tables
			vector< vector <hTableNode> > hashTable;       // hash table
			
		}
		else if(method == "Hypercube"){
			
			
			
		}
		else{
			cout << "This method does not exist..." << endl;
		}
	}
	return 0;
}
