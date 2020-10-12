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

vector<double> get_s(double w, int d){
	
	const double range_from  = 0;
    const double range_to    = w;
    
    vector<double> sVec;
    
    random_device rand_dev;
    mt19937 generator(rand_dev());
    uniform_real_distribution<double>  distr(range_from, range_to);
 
    for (int i = 0; i < d; ++i){
        sVec.push_back(distr(generator));
    }
	
	return sVec;
}

vector<int> calculate_a(vector<unsigned char> pVec, vector<double> sVec, double w, int d){			//an argei na to kanoume ena-ena
	
	int i;
	
	vector<int> aVec;
	
	for(i = 0; i < d; ++i){
		
		aVec.push_back(floor(abs(pVec[i] - sVec[i])/w));
		//cout << sVec[i] << endl;
		cout << aVec[i] << endl << endl;
		
	}
	
	return aVec;
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
