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


vector<int> get_s(double w, int d){
	const double range_from  = 0;
    const double range_to    = w;
    
    vector<int> sVec;
    
    random_device rand_dev;
    mt19937 generator(rand_dev());
    uniform_int_distribution<int> distr(range_from, range_to);
 
    for (int i = 0; i < d; ++i){
        sVec.push_back(distr(generator));
    }
	
	return sVec;
}


vector<int> calculate_a(vector<unsigned char> pVec, vector<int> sVec, double w, int d){			//an argei na to kanoume ena-ena
	vector<int> aVec;
	
	for(int i = 0; i < d; i++){
		aVec.push_back(floor((pVec[i]+w - sVec[i])/w));
		//cout << aVec[i] << endl;
	}
	
	return aVec;
}


int calculate_h(vector<int> aVec, int m, int M, int d){
	int h = 0, j, x;
	j = d-1;

	for(int i = 0; i < d; i++){									//modulo
		x = ((aVec[j]%M) * (m^i)%M) % M;

		h += x % M;
		j--;
	}
	
	h = h % M;
	
	return h;
}

int calculate_g(vector<int> hVec){
	
	int g;
	
	bitset<8> x1(hVec[0]);
	cout << "h1 is: " << x1 << endl;

	bitset<8> x2(hVec[1]);
	cout << "h2 is: " << x2 << endl;

	bitset<8> x3(hVec[2]);
	cout << "h3 is: " << x3 << endl;

	bitset<8> x4(hVec[3]);
	cout << "h4 is: " << x4 << endl;


	g = (hVec[0] << 24) | (hVec[1] << 16) | (hVec[2] << 8) | (hVec[3]);

	bitset<32> x(g);
	cout << "g is: " << x << endl;
	cout << "g(int) is: " << g << endl;
	
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
