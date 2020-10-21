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
		//~ cout << "aVec[" << i << "] = " << floor((pVec[i] - sVec[i])/w) << endl;
		aVec.push_back(floor((pVec[i] - sVec[i])/w));
	}
	
	return aVec;
}

int modular_pow(int base, int exponent, int modulus){
    if(modulus == 1){									//check if useless
        return 0;
    }
    
    int c = 1;
    
    for(int e_prime = 0; e_prime < exponent; e_prime++){
        c = (c * base) % modulus;
    }
    
    return c;
}

int calculate_h(vector<int> aVec, int m, int M, int d){
	int h = 0, j, x;
	j = d-1;

	for(int i = 0; i < d; i++){									//modulo
		x = ((aVec[j]%M) * modular_pow(m, i, M)) % M;
		//cout << "pow(m,i)%M = " << (int)pow(m,i) << " Modular exponentiation = " << modular_pow(m, i, M) << endl;
		//cout << "x = " << x << endl;
		if(x < 0)
			x += M;
		//cout << "x after = " << x << endl;
		h += x % M;
		j--;
	}
	//cout << endl << "==============================" << endl << endl;
	h = h % M;
	
	//cout << endl << endl << "==============================" << endl << endl << "h = " << h << endl << endl << "=============================="<< endl << endl << endl;
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


vector<distanceNode> approximate_nearest_neighbor(vector<unsigned char> qVec, vector < vector< vector <hTableNode> > > lHashTables, int L, int pos, int d, int N, ofstream &ofile){
	unsigned int temp;
	distanceNode node;
	vector<distanceNode> distances;
	bool flag;
	
	for(int i = 0; i < N; i++){
		node.pPos = -1;
		node.dist = 4294967295;                        //highest possible unsigned int
		distances.push_back(node);							
	}
	
	for(int i = 0; i < L; i++){
		for(int j = 0; j < lHashTables[i][pos].size(); j++){
			temp = manhattan_dist(qVec, lHashTables[i][pos][j].pVec, d);
			if(temp < distances[N-1].dist){
				flag = 0;
				for (int c=0; c<N; c++){
					if (distances[c].pPos == lHashTables[i][pos][j].pPos){
						flag = 1;
					}
				}
				
				if (flag == 0){
					distances[N-1].dist = temp;
					distances[N-1].pPos = lHashTables[i][pos][j].pPos;
					for(int c=N-2; c>=0; c--){
						if(distances[c].dist > distances[c+1].dist){
							iter_swap(distances.begin() + c, distances.begin() + c+1);
						}
						else{
							break;
						}
					}
				}
			}
		}
	}
	return distances;
 }


vector<distanceNode> actual_nearest_neighbor(vector<unsigned char>  qVec, vector< vector< unsigned char> > pVec, int d, int N, ofstream &ofile){
	unsigned int temp;							
	distanceNode node;
	vector<distanceNode> distances;

	for(int i = 0; i < N; i++){
		node.pPos = -1;
		node.dist = 4294967295;                        //highest possible unsigned int
		distances.push_back(node);							
	}                            
			
	for( int j = 0; j < pVec.size(); j++){
		temp = manhattan_dist(qVec, pVec[j], d);
		if(temp < distances[N-1].dist){
			
			distances[N-1].dist = temp;
			distances[N-1].pPos = j;
			for(int c=N-2; c>=0; c--){
				if(distances[c].dist > distances[c+1].dist){
					iter_swap(distances.begin() + c, distances.begin() + c+1);
				}
				else{
					break;
				}
			}
		}
	}
	return distances;
}


vector<distanceNode> approximate_range_search(vector<unsigned char> qVec, vector < vector< vector <hTableNode> > > lHashTables, int L, int pos, int d, double R, ofstream &ofile){
	unsigned int temp;
	vector<distanceNode> distances;
	distanceNode node;
	bool flag;
	
	for(int i = 0; i < L; i++){
		for(int j = 0; j < lHashTables[i][pos].size(); j++){
			temp = manhattan_dist(qVec, lHashTables[i][pos][j].pVec, d);
			if(temp < R){
				flag = 0;
				for (int c=0; c<distances.size(); c++){
					if (distances[c].pPos == lHashTables[i][pos][j].pPos){
						flag = 1;
					}
				}

				if (flag == 0){
					node.pPos = j;
					node.dist = temp;
					distances.push_back(node);
				}
			}
		}
	}
	return distances;
 }











