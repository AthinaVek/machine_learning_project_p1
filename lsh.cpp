#include "help_functions.h"
#include "calculations.h"

#define m 536870912

using namespace std;


int main(int argc, char** argv){
	string iFile, qFile, oFile;
	int i, k, L, N;
	double R, w;
	
	if(argc == 15)
	{
		for (int i = 1; i < 15; ++i)
		{
			if (argv[i] == "-d")
			{
				iFile = argv[i+1];
			}
			else if (argv[i] == "-q")
			{
				qFile = argv[i+1];
			}
			else if (argv[i] == "-k")
			{
				k = atoi(argv[i+1]);
			}
			else if (argv[i] == "-L")
			{
				L = atoi(argv[i+1]);
			}
			else if (argv[i] == "-o")
			{
				oFile = argv[i+1];
			}
			else if (argv[i] == "-N")
			{
				N = atoi(argv[i+1]);
			}
			else if (argv[i] == "-R")
			{
				R = atoi(argv[i+1]);
			}
		}
	}
	else{
		// cout << "Error: Wrong input." << endl;    //THE RIGHT ELSE
		// return 0;



		//Delete the above:                          //THE DEBUG ELSE
		iFile = "train-images-idx3-ubyte";
		
		k = 4;				//default values if not given by user
		L = 5;
		N = 1;
		R = 1.0;
		
		w = 10 * R;
		
	}
	
	ifstream file (iFile);
    if (file.is_open())
    {
        int magic_number=0, number_of_images=0;
        int n_rows=0, n_cols=0;
        int d, M;
        int h;
        
        unsigned int g;
        
        M = pow(2,(32/k));
		
		vector< vector<unsigned char> > pVec; 
    	vector<unsigned char> tempVec;
		vector< vector<int> > sVec;
		vector<int> aVec;
		vector< vector<int> > hVec;
		vector<int> tempIntVec;
		vector<unsigned int> gVec;
		
        file.read((char*)&magic_number,sizeof(magic_number)); 
        magic_number = reverseInt(magic_number);
        file.read((char*)&number_of_images,sizeof(number_of_images));
        number_of_images = reverseInt(number_of_images);
        file.read((char*)&n_rows,sizeof(n_rows));
        n_rows = reverseInt(n_rows);
        file.read((char*)&n_cols,sizeof(n_cols));
        n_cols = reverseInt(n_cols);
        
        d = n_rows * n_cols;						//dimension

        //list< list<unsigned char> > pList; 
    	//list<unsigned char> tempList; 
		
        for(int i = 0; i < number_of_images; i++)
        {
            for(int r = 0; r < n_rows; r++)
            {
                for(int c = 0; c < n_cols; c++)
                {
                    unsigned char temp = 0;
                    file.read((char*)&temp,sizeof(temp));

                    tempVec.push_back(temp);
                }
            }
            pVec.push_back(tempVec);
            tempVec.erase(tempVec.begin(), tempVec.end());
            
        }


        //~ for (int i = 0; i < k; i++){
        	//~ sVec = get_s(w, d);							//s_i uniform random generator

        	//~ for (int j = 0; j < number_of_images; j++){
				//~ aVec = calculate_a(pVec[j], sVec, w, d);
				//~ h = calculate_h(aVec, m, M, d);
				//~ tempHVec.push_back(h);
        		//~ //cout << h << endl;
        	//~ }
        	//~ hVec.push_back(tempHVec);
        	//~ tempHVec.erase(tempHVec.begin(), tempHVec.end());
        	
        	//~ aVec = calculate_a(pVec[0], sVec, w, d);
        	//~ h = calculate_h(aVec, m, M, d);
        	//~ hVec.push_back(h);
        //~ }


        for (int i=0; i<k; i++){
			tempIntVec = get_s(w, d);        //s_i uniform random generator
			sVec.push_back(tempIntVec);
			tempIntVec.erase(tempIntVec.begin(), tempIntVec.end());
        }
        
        for (int i = 0; i < number_of_images; i++){
			for (int j = 0; j < k; j++){
				aVec = calculate_a(pVec[i], sVec[j], w, d);
				h = calculate_h(aVec, m, M, d);
				tempIntVec.push_back(h);
			}
			hVec.push_back(tempIntVec);
        	tempIntVec.erase(tempIntVec.begin(), tempIntVec.end());
        	
        	g = calculate_g(hVec[i], k);
        	gVec.push_back(g);
		}
		
    }
	
	
	return 0;
}
