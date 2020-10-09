#include <iostream>
#include <cstdlib>

using namespace std;

int main(int argc, char** argv){
	
	int i, k, L, N;
	double R;
	
	if(argc == 5){
		k = atoi(argv[1]);
		L = atoi(argv[2]);
		N = atoi(argv[3]);
		R = atof(argv[4]);
	}
	else{
		k = 4;
		L = 5;
		N = 1;
		R = 1.0;
	}
	
	
	
	
	return 0;
}
