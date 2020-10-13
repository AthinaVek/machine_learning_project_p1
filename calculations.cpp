#include "calculations.h"


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
	//cout << "h1 is: " << x1 << endl;

	bitset<8> x2(hVec[1]);
	//cout << "h2 is: " << x2 << endl;

	bitset<8> x3(hVec[2]);
	//cout << "h3 is: " << x3 << endl;

	bitset<8> x4(hVec[3]);
	//cout << "h4 is: " << x4 << endl;


	g = (hVec[0] << 24) | (hVec[1] << 16) | (hVec[2] << 8) | (hVec[3]);

	bitset<32> x(g);
	//cout << "g is: " << x << endl;
	//cout << "g(int) is: " << g << endl;
	
}
