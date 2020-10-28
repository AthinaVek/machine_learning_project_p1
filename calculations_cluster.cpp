#include "calculations_cluster.h"


void k_means_init(vector< vector<unsigned char> > &centroids, int number_of_images, vector< vector<unsigned char> > pVec, int k, int d){
	
	int random, t = 0, y;
	float x, max, min;
	unsigned int dist;
	
	vector<float> p;
	
	random = rand() % number_of_images + 0;
	centroids.push_back(pVec[random]);										//first centroid chosen randomly
	t++;																	//current centroids++
	
	p.push_back(0);															//p(0) = 0
	
	while(t < k){
		
		for(int i = 1; i < number_of_images; i++){								//for every image
			max = 0;
			min = 4294967295;                                       			//highest possible unsigned int
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
}

void lloyds_assignment(vector< vector<int> > &clusters, vector< vector<int> > temp, int number_of_images, vector< vector<unsigned char> > pVec, vector< vector<unsigned char> > centroids, int k, int d, int *changes, int first){
	
	int minc;
	float min;
	unsigned int dist;
	bool notFound;
	
	
	
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
				notFound = 1;
				for(int z = 0; z < clusters[i].size(); z++){
					if(temp[i][j] == clusters[i][z]){
						notFound = 0;
					}
				}
				*changes += notFound;
				if (*changes > 5)
					break;
			}
			if (*changes > 5)
				break;
		}
	}
		
	clusters = temp;
	temp.erase(temp.begin(), temp.end());
	
}

void update_centroids_median(vector< vector<unsigned char> > &centroids, vector <unsigned char> pDim, vector< vector<unsigned char> > pVec, vector< vector<int> > clusters, vector <unsigned char> tempC, int k, int d){
	
	double cSize;
	int median;
	
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
}

