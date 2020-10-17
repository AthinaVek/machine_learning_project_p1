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
		x = ((aVec[j]%M) * (m^i)%M) % M;						//pow(m,i)

		h += x % M;
		j--;
	}
	
	h = h % M;
	
	return h;
}

unsigned int calculate_g(vector<int> hVec, int k){
	unsigned int g=0;
	
	// bitset<8> x1(hVec[0]);
	// cout << "h1 is: " << x1 << endl;

	// bitset<8> x2(hVec[1]);
	// cout << "h2 is: " << x2 << endl;

	// bitset<8> x3(hVec[2]);
	// cout << "h3 is: " << x3 << endl;

	// bitset<8> x4(hVec[3]);
	// cout << "h4 is: " << x4 << endl;

	for (int i=0; i<k; i++){
		g = hVec[i] << (k-1-i)*8 | g ;
	}

	//bitset<32> x(g);
	//cout << "g is: " << x << endl;
	// cout << "g(int) is: " << g << endl;

	return g;
	
}

unsigned int manhattan_dist(vector<unsigned char> qVec, vector<unsigned char> pVec, int d){
	
	unsigned int dist = 0;
	
	for(int i = 0; i < d; i++){
		dist+= abs(qVec[i] - pVec[i]);
	}
	
	return dist;
	
}

unsigned int approximate_nearest_neighbor(vector<unsigned char> qVec, vector < vector< vector <vector<unsigned char> > > > lHashTables, int L, int pos, int d, int N){
	
	 unsigned int temp;							//highest possible unsigned int
	 vector<unsigned int> distances[N];
	
	 for(int i = 0; i < N; i++){
		
		 distances[i] = 4294967295;
		
	 }
	
	 for(int i = 0; i < L; i++){
		
		 for(int j = 0; j < lHashTables[i][pos].size(); j++){
			
			 temp = manhattan_dist(qVec, lHashTables[i][pos][j], d);
			 if(temp < distances[N-1]){
				
				 for(int c = 0; c < N; c++){
					
					 if(temp < distances[c]){
						// vector<int> v{1,2,3,4,5};
	
						// for(int i=3;i>0;i--){
							// iter_swap(v.begin() + i, v.begin() + i+1);
						// }
											
					 }
					
				 }
				
				 //number of neighbor
			 }
			
		 }
		
	 }
	
	 //return dist;
	
 }

unsigned int actual_nearest_neighbor(vector<unsigned char>  qVec, vector< vector< unsigned char> > pVec, int d){
	
	unsigned int dist = 4294967295, temp;							//highest possible unsigned int
			
	for( int j = 0; j < pVec.size(); j++){
		
		temp = manhattan_dist(qVec, pVec[j], d);
		
		if(temp < dist){
			dist = temp;
			
			//number of neighbor
		}
		
	}
	
	return dist;
	
}











