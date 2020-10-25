#include "help_functions.h"
#include "calculations.h"
#include "calculations_lsh.h"
#include "calculations_cube.h"


using namespace std;


int main(int argc, char** argv){
	
	string iFile, confFile, oFile, method;
	int magic_number=0, number_of_images=0;
    int n_rows=0, n_cols=0;
    int d;
    
	vector< vector<unsigned char> > pVec; 
	vector<unsigned char> tempVec;
	vector< vector<unsigned char> > centroids;
	
	srand (time(NULL));
	
	if(read_inputCluster(&argc, argv, &iFile, &confFile, &oFile, &method)){
		
		//read_confFile();
		
		ifstream file (iFile);
		if (file.is_open()){
			read_data(file, &magic_number, &number_of_images, &n_rows, &n_cols, pVec, tempVec);
			
			d = n_rows * n_cols;
			
			centroids.push_back(pVec[rand() % number_of_images + 0]);					//first centroid chosen randomly
			
			//vector with distances from centroids
			
			
			
		}
		
		
		
		
	}
	
	
	
	
}
