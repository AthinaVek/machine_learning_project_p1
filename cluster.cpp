#include "help_functions.h"
#include "calculations.h"
#include "calculations_lsh.h"
#include "calculations_cube.h"

#define k 10

using namespace std;


int main(int argc, char** argv){
	string iFile, confFile, oFile, method;
	int magic_number=0, number_of_images=0;
    int n_rows=0, n_cols=0, d;
    int K, L, kl, M, ky, probes; 
    int y, random, t = 0, minc, changes = 6;
    unsigned int dist;
    float x, max = 0, min;
    
	vector< vector<unsigned char> > pVec; 
	vector<unsigned char> tempVec;
	vector< vector<unsigned char> > centroids;
	vector<float> p;
	vector<vector<clusterNode> > clusters;
	
	srand (time(NULL));
	
	if(read_inputCluster(&argc, argv, &iFile, &confFile, &oFile, &method)){
		read_confFile(&K, &L, &kl, &M, &ky, &probes, confFile);

		ifstream file (iFile);
		if (file.is_open()){
			read_data(file, &magic_number, &number_of_images, &n_rows, &n_cols, pVec, tempVec);
			
			d = n_rows * n_cols;
			
			random = rand() % number_of_images + 0;
			centroids.push_back(pVec[random]);										//first centroid chosen randomly
			t++;
			
			p.push_back(0);															//p(0) = 0
			
			while(t < k){
				
				for(int i = 1; i < number_of_images; i++){								//for every image
					max = 0;
					min = 4294967295;                      								//highest possible unsigned int
					for(int j = 0; j < t; j++){											//for every centroid
						
						dist = manhattan_dist(pVec[i], centroids[j], d);
						
						if(dist < min)
							min = (float)dist;
						
						if(dist > max)
							max = (float)dist;
						
					}
					
					min = min / max;												//divide by max(d_i) to avoid large numbers
					
					min = pow(min,2);
					min += p[i-1];													//calculate sum of d_i^2
					
					p.push_back(min);												//vector with min distances from centroids
					
				}
				
				x = get_x(p[number_of_images - t]);									//find random x in [0,P(n-t)]
				
				for(y = 0; y < p.size(); y++){
					
					if(x < p[y])													//ceiling of range of x is the index of the new centroid
						break;
				}
				centroids.push_back(pVec[y]);
				t++;
			}
			
			while(changes > 5){
				changes = 0;
				for(int i = 1; i < number_of_images; i++){								//assign each image to centroids
					
					min = 4294967295;                      								//highest possible unsigned int
					
					for(int j = 0; j < k; j++){											//for every centroid
							
						dist = manhattan_dist(pVec[i], centroids[j], d);
						
						if(dist < min){
							min = (float)dist;
							minc = j;
						}
						
					}
					clusters[j].push_back(pVec[i]);
					
				}
			
			}
		}
		
	}
	
	
	return 0;
}
