#include <iostream>
#include <vector>
#include <random>

#include "help_functions.h"

int reverseInt (int i){
    unsigned char c1, c2, c3, c4;

    c1 = i & 255;
    c2 = (i >> 8) & 255;
    c3 = (i >> 16) & 255;
    c4 = (i >> 24) & 255;

    return ((int)c1 << 24) + ((int)c2 << 16) + ((int)c3 << 8) + c4;
}

void read_input(int* argc, char** argv, string* iFile, string* qFile, int* k, int* L, string* oFile, int* N, double* R, double* w){
	
	if(*argc == 15){                                          // Read input
		for (int i = 1; i < 15; ++i){
			if (string(argv[i]) == "-d"){
				*iFile = argv[i+1];
			}
			else if (string(argv[i]) == "-q"){
				*qFile = argv[i+1];
			}
			else if (string(argv[i]) == "-k"){
				*k = atoi(argv[i+1]);
			}
			else if (string(argv[i]) == "-L"){
				*L = atoi(argv[i+1]);
			}
			else if (string(argv[i]) == "-o"){
				*oFile = argv[i+1];
			}
			else if (string(argv[i]) == "-N"){
				*N = atoi(argv[i+1]);
			}
			else if (string(argv[i]) == "-R"){
				*R = atof(argv[i+1]);
			}
		}
	}
	else{
		cout << "No right input given. Using default values." << endl << endl;

		*iFile = "train-images-idx3-ubyte";                   //default values if not given by user
		*qFile = "t10k-images-idx3-ubyte";
		*oFile = "lsh_results.txt";
		
		*k = 4;				
		*L = 5;
		*N = 7;
		*R = 10000;
		
	}
	
	*w = 8 * (*R);
	
}



// void printNestedList(list<list<unsigned char> > nested_list) 
// { 
//     cout << "[\n"; 
  
//     // nested_list`s iterator(same type as nested_list) 
//     // to iterate the nested_list 
//     list<list<unsigned char> >::iterator nested_list_itr; 
  
//     // Print the nested_list 
//     for (nested_list_itr = nested_list.begin(); 
//          nested_list_itr != nested_list.end(); 
//          ++nested_list_itr) { 
  
//         cout << "  ["; 
  
//         // normal_list`s iterator(same type as temp_list) 
//         // to iterate the normal_list 
//         list<unsigned char>::iterator single_list_itr; 
  
//         // pointer of each list one by one in nested list 
//         // as loop goes on 
//         list<unsigned char>& single_list_pointer = *nested_list_itr; 
  
//         for (single_list_itr = single_list_pointer.begin(); 
//              single_list_itr != single_list_pointer.end(); 
//              single_list_itr++) { 
//             cout << " " << *single_list_itr << " "; 
//         } 
//         cout << "]\n"; 
//     } 
//     cout << "]"; 
// } 
