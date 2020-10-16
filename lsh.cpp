#include "help_functions.h"
#include "calculations.h"

#define m 536870912    // 2^29
#define NForTable 16

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
		k = 4;				
		L = 5;
		N = 1;
		R = 1.0;
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

        for(int i = 0; i < number_of_images; i++){             // read image
            for(int r = 0; r < n_rows; r++){
                for(int c = 0; c < n_cols; c++){
                    unsigned char temp = 0;
                    file.read((char*)&temp,sizeof(temp));

                    tempVec.push_back(temp);
                }
            }
            pVec.push_back(tempVec);                           // save vector of pixels for every image
            tempVec.erase(tempVec.begin(), tempVec.end());
        }

		// for L
        vector< vector <vector<unsigned char> > > hashTable;       // hash table
        for(int y=0; y<hTableSize; y++){
		    hashTable.push_back(vector<vector<unsigned char> >()); //initialize the first index with a 2D vector
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
	
    }
	return 0;
}
