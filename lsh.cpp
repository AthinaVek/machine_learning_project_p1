#include <iostream>
#include <cstdlib>
#include <fstream>
#include <bits/stdc++.h>
#include <string>

using namespace std;


int reverseInt (int i) 
{
    unsigned char c1, c2, c3, c4;

    c1 = i & 255;
    c2 = (i >> 8) & 255;
    c3 = (i >> 16) & 255;
    c4 = (i >> 24) & 255;

    return ((int)c1 << 24) + ((int)c2 << 16) + ((int)c3 << 8) + c4;
}

int main(int argc, char** argv){
	string iFile, qFile, oFile;
	int i, k, L, N;
	double R;
	
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
	}
	
	ifstream file (iFile);
    if (file.is_open())
    {
        int magic_number=0;
        int number_of_images=0;
        int n_rows=0;
        int n_cols=0;
        file.read((char*)&magic_number,sizeof(magic_number)); 
        magic_number = reverseInt(magic_number);
        file.read((char*)&number_of_images,sizeof(number_of_images));
        number_of_images = reverseInt(number_of_images);
        file.read((char*)&n_rows,sizeof(n_rows));
        n_rows = reverseInt(n_rows);
        file.read((char*)&n_cols,sizeof(n_cols));
        n_cols = reverseInt(n_cols);
        
        cout << magic_number << endl;
        cout << number_of_images << endl;
        cout << n_rows << endl;
        cout << n_cols << endl;

        for(int i=0;i<number_of_images;++i)
        {
            for(int r=0;r<n_rows;++r)
            {
                for(int c=0;c<n_cols;++c)
                {
                    unsigned char temp=0;
                    file.read((char*)&temp,sizeof(temp));
                    // cout << temp << endl;
                }
            }
        }
    }
	
	
	return 0;
}
