#include "calculations_cube.h"

unsigned int calculate_p(vector<fNode> fVec, int k){
	unsigned int p=0;

	for (int i=0; i<k; i++){
		p = fVec[i].f << (k-1-i) | p ;
	}
	// cout << "///" << p << endl;
	// p = (int)p | (int)pow(2,k);
	// cout << p << endl;
	return p;
}
