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
		x = ((aVec[j]%M) * (int)pow(m,i)%M) % M;						//pow(m,i)

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


void approximate_nearest_neighbor(vector<unsigned char> qVec, vector < vector< vector <vector<unsigned char> > > > lHashTables, int L, int pos, int d, int N, ofstream &ofile){
	unsigned int temp;
	vector<unsigned int> distances;
	
	for(int i = 0; i < N; i++){
		distances.push_back(4294967295);							//highest possible unsigned int
	}
	
	for(int i = 0; i < L; i++){

		for(int j = 0; j < lHashTables[i][pos].size(); j++){
			temp = manhattan_dist(qVec, lHashTables[i][pos][j], d);
			if(temp < distances[N-1]){
				
				distances[N-1] = temp;
				for(int c=N-2; c>=0; c--){
					if(distances[c] > distances[c+1]){
						iter_swap(distances.begin() + c, distances.begin() + c+1);
					}
					else{
						break;
					}
				}
				 //number of neighbor
			}
		}
	}
	if (distances.size() == 0){
		ofile << "No neighbors." << endl << endl;
	}
	else{
		for(int c=0; c<N-1; c++){
			ofile << distances[c] << ", ";
		}
		ofile << distances[N-1] << endl;
	}
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



void approximate_range_search(vector<unsigned char> qVec, vector < vector< vector <vector<unsigned char> > > > lHashTables, int L, int pos, int d, double R, ofstream &ofile){
	unsigned int temp;
	int c;
	vector<unsigned int> distances;
	
	for(int i = 0; i < L; i++){

		for(int j = 0; j < lHashTables[i][pos].size(); j++){
			temp = manhattan_dist(qVec, lHashTables[i][pos][j], d);
			// cout << lHashTables[i][pos].size() << "    " << j << endl;
			if(temp < R){
				distances.push_back(temp);
			}
		}
	}

	if (distances.size() == 0){
		ofile << "No neighbors in this range." << endl << endl;
	}
	else{
		for(c=0; c<distances.size()-1; c++){
			// cout << distances.size()-1 << "    " << c << endl;
			ofile << distances[c] << ", ";
		}

		ofile << distances[c] << endl << endl;
	}
 }











