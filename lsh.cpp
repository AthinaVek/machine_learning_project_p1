#include "help_functions.h"
#include "calculations.h"

#include <algorithm>

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
    int d, M, h, pos;
    unsigned int g;
    int hTableSize;

	vector< vector<unsigned char> > pVec; 
	vector<unsigned char> tempVec;
	vector< vector<int> > sVec;
	vector<int> aVec;
	vector< vector<int> > hVec;
	vector<int> tempIntVec;
	vector< vector<unsigned char> > qVec;

	hTableNode node;
	
	if(argc == 15){                                          // Read input
		for (int i = 1; i < 15; ++i){
			if (string(argv[i]) == "-d"){
				iFile = argv[i+1];
			}
			else if (string(argv[i]) == "-q"){
				qFile = argv[i+1];
			}
			else if (string(argv[i]) == "-k"){
				k = atoi(argv[i+1]);
			}
			else if (string(argv[i]) == "-L"){
				L = atoi(argv[i+1]);
			}
			else if (string(argv[i]) == "-o"){
				oFile = argv[i+1];
			}
			else if (string(argv[i]) == "-N"){
				N = atoi(argv[i+1]);
			}
			else if (string(argv[i]) == "-R"){
				R = atof(argv[i+1]);
			}
		}
	}
	else{
		cout << "No right input given. Using default values." << endl << endl;

		iFile = "train-images-idx3-ubyte";                   //default values if not given by user
		qFile = "t10k-images-idx3-ubyte";
		oFile = "lsh_results.txt";
		k = 4;				
		L = 5;
		N = 7;
		R = 10000;
		w = 8 * R;
	}
	
	M = pow(2,(32/k));
	
	ifstream file (iFile);
    if (file.is_open()){
        
		file.read((char*)&magic_number,sizeof(magic_number));    // read values from file
        magic_number = reverseInt(magic_number);
        file.read((char*)&number_of_images,sizeof(number_of_images));
        number_of_images = reverseInt(number_of_images);
        file.read((char*)&n_rows,sizeof(n_rows));
        n_rows = reverseInt(n_rows);
        file.read((char*)&n_cols,sizeof(n_cols));
        n_cols = reverseInt(n_cols);
        
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
		
		d = n_rows * n_cols;						           // dimension
        hTableSize = number_of_images / NForTable;
        
        vector < vector< vector <hTableNode> > > lHashTables;       // vector with L hash tables
        vector< vector <hTableNode> > hashTable;       // hash table

		for (int l=0; l<L; l++){
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
					tempIntVec.push_back(h);
				}
				hVec.push_back(tempIntVec);                      // save k*h of every image
	        	tempIntVec.erase(tempIntVec.begin(), tempIntVec.end());
	        	
	        	g = calculate_g(hVec[i], k);                  // calculate g for every image
	        	pos = g % hTableSize;                         // find the position to insert the image in the hash table

	        	node.pPos = i;
	        	node.g = g;
	        	node.pVec = pVec[i];
	        	hashTable[pos].push_back(node);            // insert image in the hash table
			}

			lHashTables.push_back(hashTable);
			hashTable.erase(hashTable.begin(), hashTable.end());
		}


		ifstream qfile (qFile);
	    if (qfile.is_open()){
			qfile.read((char*)&magic_number,sizeof(magic_number));    // read values from file
	        magic_number = reverseInt(magic_number);
	        qfile.read((char*)&number_of_images,sizeof(number_of_images));
	        number_of_images = reverseInt(number_of_images);
	        qfile.read((char*)&n_rows,sizeof(n_rows));
	        n_rows = reverseInt(n_rows);
	        qfile.read((char*)&n_cols,sizeof(n_cols));
	        n_cols = reverseInt(n_cols);
	        
	        for(int i = 0; i < number_of_images; i++){             // read image
	            for(int r = 0; r < n_rows; r++){
	                for(int c = 0; c < n_cols; c++){
	                    unsigned char temp = 0;
	                    qfile.read((char*)&temp,sizeof(temp));

	                    tempVec.push_back(temp);
	                }
	            }
	            qVec.push_back(tempVec);                           // save vector of pixels for every image
	            tempVec.erase(tempVec.begin(), tempVec.end());
	        }

	    	ofstream ofile (oFile);
			if (ofile.is_open()){
				for(int i = 0; i < 20; i++){
					
					for (int j = 0; j < k; j++){
						aVec = calculate_a(qVec[i], sVec[j], w, d);  // calculate a for every image
						h = calculate_h(aVec, m, M, d);              // calculate h for every image
						tempIntVec.push_back(h);
					}
					
					g = calculate_g(tempIntVec, k);                  // calculate g for every image
					pos = g % hTableSize;                         // find the position to insert the image in the hash table
					
					// approximate_nearest_neighbor(qVec[i], lHashTables, L, pos, d, N, ofile);
					
					// actual_nearest_neighbor(qVec[i], pVec, d, ofile);

					approximate_range_search( qVec[i], lHashTables, L, pos, d, R, ofile);
					
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
