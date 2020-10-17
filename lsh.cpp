#include "help_functions.h"
#include "calculations.h"

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
    int d, M, h, pos, z;
    unsigned int g;
    int hTableSize;

	vector< vector<int> > pVec; 
	vector<int> tempVec;
	vector< vector<int> > sVec;
	vector<int> aVec;
	vector< vector<int> > hVec;
	vector<int> tempIntVec;
	vector<int> qVec;
	
	if(argc == 15){                                          // Read input
		for (int i = 1; i < 15; ++i){
			if (argv[i] == "-d"){
				iFile = argv[i+1];
			}
			else if (argv[i] == "-q"){
				qFile = argv[i+1];
			}
			else if (argv[i] == "-k"){
				k = atoi(argv[i+1]);
			}
			else if (argv[i] == "-L"){
				L = atoi(argv[i+1]);
			}
			else if (argv[i] == "-o"){
				oFile = argv[i+1];
			}
			else if (argv[i] == "-N"){
				N = atoi(argv[i+1]);
			}
			else if (argv[i] == "-R"){
				R = atof(argv[i+1]);
			}
		}
	}
	else{
		cout << "No input given. Using default values." << endl << endl;

		iFile = "train-images-idx3-ubyte";                   //default values if not given by user
		qFile = "t10k-images-idx3-ubyte";
		k = 4;				
		L = 5;
		N = 1;
		R = 10000;
		w = 10 * R;
	}
	
	ifstream file (iFile);
    if (file.is_open()){
        M = pow(2,(32/k));
		
        file.read((char*)&magic_number,sizeof(magic_number));    // read values from file
        magic_number = reverseInt(magic_number);
        file.read((char*)&number_of_images,sizeof(number_of_images));
        number_of_images = reverseInt(number_of_images);
        file.read((char*)&n_rows,sizeof(n_rows));
        n_rows = reverseInt(n_rows);
        file.read((char*)&n_cols,sizeof(n_cols));
        n_cols = reverseInt(n_cols);
        
        d = n_rows * n_cols;						           // dimension
        hTableSize = number_of_images / NForTable;

        for(int i = 0; i < 1; i++){             // read image
            for(int r = 0; r < n_rows; r++){
                for(int c = 0; c < n_cols; c++){
                    unsigned char temp = 0;
                    file.read((char*)&temp,sizeof(temp));
                    z = (int)temp;
                    tempVec.push_back(z);
                }
            }
            pVec.push_back(tempVec);                           // save vector of pixels for every image
            tempVec.erase(tempVec.begin(), tempVec.end());
        }

        vector < vector< vector <vector<int> > > > lHashTables;       // vector with L hash tables
        vector< vector <vector<int> > > hashTable;       // hash table

		for (int l=0; l<L; l++){
	        for(int y=0; y<hTableSize; y++){
			    hashTable.push_back(vector<vector<int> >()); //initialize the first index with a 2D vector
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
	        	hashTable[pos].push_back(pVec[i]);            // insert image in the hash table
			}
		
			// for (int i=0; i<hTableSize; i++){
			// 	cout << l << "lllll" << i << "------" << hashTable[i].size() << endl;
			// }

			lHashTables.push_back(hashTable);
			hashTable.erase(hashTable.begin(), hashTable.end());
		}




		ifstream file (qFile);
	    if (file.is_open()){
			for(int r = 0; r < n_rows; r++){
	            for(int c = 0; c < n_cols; c++){
	                unsigned char temp = 0;
	                file.read((char*)&temp,sizeof(temp));
	                z = (int)temp;
	                qVec.push_back(temp);
	            }
	        }

	    unsigned int dist;

	 //    vector <int> arr1 = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,84,185,159,151,60,36,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,222,254,254,254,254,241,198,198,198,198,198,198,198,198,170,52,0,0,0,0,0,0,0,0,0,0,0,0,67,114,72,114,163,227,254,225,254,254,254,250,229,254,254,140,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,17,66,14,67,67,67,59,21,236,254,106,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,83,253,209,18,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,22,233,255,83,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,129,254,238,44,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,59,249,254,62,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,133,254,187,5,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,9,205,248,58,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,126,254,182,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,75,251,240,57,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,19,221,254,166,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,203,254,219,35,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,38,254,254,77,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,31,224,254,115,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,133,254,254,52,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,61,242,254,254,52,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,121,254,254,219,40,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,121,254,207,18,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
		// vector <int> arr2 = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,18,18,18,126,136,175,26,166,255,247,127,0,0,0,0,0,0,0,0,0,0,0,0,30,36,94,154,170,253,253,253,253,253,225,172,253,242,195,64,0,0,0,0,0,0,0,0,0,0,0,49,238,253,253,253,253,253,253,253,253,251,93,82,82,56,39,0,0,0,0,0,0,0,0,0,0,0,0,18,219,253,253,253,253,253,198,182,247,241,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,80,156,107,253,253,205,11,0,43,154,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,14,1,154,253,90,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,139,253,190,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,11,190,253,70,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,35,241,225,160,108,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,81,240,253,253,119,25,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,45,186,253,253,150,27,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,16,93,252,253,187,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,249,253,249,64,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,46,130,183,253,253,207,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,39,148,229,253,253,253,250,182,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,24,114,221,253,253,253,253,201,78,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,23,66,213,253,253,253,253,198,81,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,18,171,219,253,253,253,253,195,80,9,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,55,172,226,253,253,253,253,244,133,11,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,136,253,253,253,212,135,132,16,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
	 //    dist = manhattan_dist(arr1, arr2, d);

	    dist = manhattan_dist(pVec[0], qVec, d);
	    cout << dist << endl;
	    dist = manhattan_dist(pVec[1], qVec, d);
	    cout << dist << endl;
	    dist = manhattan_dist(pVec[2], qVec, d);
	    cout << dist << endl;




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
