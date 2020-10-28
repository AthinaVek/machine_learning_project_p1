#include "help_functions.h"
#include "calculations.h"
#include "calculations_lsh.h"
#include "calculations_cube.h"

using namespace std;


int main(int argc, char** argv){
	string iFile, confFile, oFile, method;
	int magic_number=0, number_of_images=0;
    int n_rows=0, n_cols=0, d;
    int k, L, kl, M, ky, probes, median; 
    int y, random, t = 0, minc, changes = 6, first=1;
    unsigned int dist;
    float x, max = 0, min;
    double cSize;
    bool notFound;
    
	vector< vector<unsigned char> > pVec; 
	vector<unsigned char> tempVec;
	vector< vector<unsigned char> > centroids;
	vector<float> p;
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
		
		random = rand() % number_of_images + 0;
		centroids.push_back(pVec[random]);										//first centroid chosen randomly
		t++;
		
		p.push_back(0);															//p(0) = 0
		
		while(t < k){
			
			for(int i = 1; i < number_of_images; i++){								//for every image
				max = 0;
				min = 4294967295;                                       //highest possible unsigned int
				for(int j = 0; j < t; j++){											//for every centroid
					dist = manhattan_dist(pVec[i], centroids[j], d);
					
					if(dist < min)
						min = (float)dist;
					if(dist > max)
						max = (float)dist;
				}

				if (t > 1){
					min = min / max;												//divide by max(d_i) to avoid large numbers
				}
				min = pow(min,2);
				min += p[i-1];													//calculate sum of d_i^2
				p.push_back(min);												//vector with min distances from centroids
			}
			
			x = get_x(p[number_of_images -1 - t]);									//find random x in [0,P(n-t)]
			
			for(y = 0; y < p.size(); y++){
				if(x < p[y]){   												//ceiling of range of x is the index of the new centroid
					break;
				}
			}
			centroids.push_back(pVec[y]);
			t++;
		}
		
		if(method == "Classic"){
			while(changes > 5){
				changes = 0;

				for(int i = 0; i < number_of_images; i++){								//assign each image to centroids
					min = 4294967295;                      								//highest possible unsigned int
					
					for(int j = 0; j < k; j++){											//for every centroid
						dist = manhattan_dist(pVec[i], centroids[j], d);

						if(dist < min){
							min = (float)dist;
							minc = j;
						}
					}
					temp[minc].push_back(i);
				}
				
				if (first == 0){
					for(int i = 0; i < k; i++){
						for(int j = 0; j < temp[i].size(); j++){
							for(int z = 0; z < clusters[i].size(); z++){
								if(temp[i][j] == clusters[i][z]){
									notFound = 0;
								}
							}
							changes += notFound;
							if (changes > 5)
								break;
						}
						if (changes > 5)
							break;
					}
					if (changes <= 5)
						break;
				}
					
				clusters = temp;
				temp.erase(temp.begin(), temp.end());
				
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
			cout << "LSH" << endl;
			
		}
		else if(method == "Hypercube"){
			cout << "Hypercube" << endl;
		}
		else{
			cout << "This method does not exist..." << endl;
		}
	}
	return 0;
}
