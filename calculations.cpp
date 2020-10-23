#include "calculations.h"


vector<int> get_s(double w, int d){
	const double range_from  = 0;
    const double range_to    = w;
    
    vector<int> sVec;
    
    random_device rand_dev;
    mt19937 generator(rand_dev());
    uniform_int_distribution<> distr(range_from, range_to);
 
    for (int i = 0; i < d; ++i){
        sVec.push_back(distr(generator));
    }
	return sVec;
}


vector<int> calculate_a(vector<unsigned char> pVec, vector<int> sVec, double w, int d){			//an argei na to kanoume ena-ena
	vector<int> aVec;
	
	for(int i = 0; i < d; i++){
		aVec.push_back(floor((pVec[i]+w - sVec[i])/w));
	}
	return aVec;
}


int modular_pow(int base, int exponent, int modulator){
    int result;

    base = base % modulator;

    while(exponent > 0){
        if( (exponent%2) != 0){                       // odd number
            result = (result * base) % modulator;
        }
        exponent = exponent >> 1;
        base = (base * base) % modulator;
    }
    return result;
}


int calculate_h(vector<int> aVec, int m, int M, int d){
	int h = 0, j, x;
	j = d-1;

	for(int i = 0; i < d; i++){									//modulo
		x = ((aVec[j]%M) * modular_pow(m, i, M)) % M;

		//cout << "pow(m,i)%M = " << (int)pow(m,i) << " Modular exponentiation = " << modular_pow(m, i, M) << endl;
		//cout << "x = " << x << endl;
		
		// if(x < 0)
		// 	x += M;
		
		//cout << "x after = " << x << endl;
		h += x % M;
		j--;
	}
	//cout << endl << "==============================" << endl << endl;
	h = h % M;
	
	//cout << endl << endl << "==============================" << endl << endl << "h = " << h << endl << endl << "=============================="<< endl << endl << endl;
	return h;
}

unsigned int manhattan_dist(vector<unsigned char> qVec, vector<unsigned char> pVec, int d){
	unsigned int dist = 0;
	
	for(int i = 0; i < d; i++){
		dist+= abs(qVec[i] - pVec[i]);
	}
	return dist;
}




