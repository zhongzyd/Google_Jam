#include <stdio.h>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

typedef struct
{
	int a[10];
}AA;

int main()
{
    ifstream fin("B-large-practice.in");
    ofstream fout("B-large-practice.out");

	int C;

    fin >> C;

    for(int i=1;i<=C;++i)
    {
		int N;
		fin >> N;

		vector<int> milkshakes;
		milkshakes.resize(N,0);

		vector<int> milkshakesSure;
		milkshakesSure.resize(N,0);

		int M;
		fin >> M;

		vector<vector<int>> customers;
		customers.resize(M);

		vector<int> customersOK;
		customersOK.resize(M,0);

		for(int j=0,T=0; j<M; j++)
		{
			fin >> T;
			customers[j].resize(T*2);
			for(int k=0; k<T*2; k+=2)
			{
				fin >> customers[j][k];
				--customers[j][k];
				
				fin >> customers[j][k+1];
			}
		}

		for(int j=0; j<M; j++)
		{
			if(customersOK[j]!=1)
				if(customers[j].size()==2)
				{
					customersOK[j]=1;

					if( milkshakesSure[customers[j][0]] == 1 )
					{
						if(milkshakes[customers[j][0]] != customers[j][1])
							goto IMPOSSIBLE;
						else
							continue;
					}

					milkshakes[customers[j][0]] = customers[j][1];
					milkshakesSure[customers[j][0]] = 1;

					int reOrNot=0;
					for(int c=0; c<M; c++)
					{
						for(int m=0; m<customers[c].size(); m+=2)
						{
							if( customers[c][m] == customers[j][0] && customers[c][m+1] == (milkshakes[customers[c][m]]? 0:1) )
							{
								customers[c].erase(customers[c].begin()+m);
								customers[c].erase(customers[c].begin()+m);
								if(customers[c].size()==0)
									goto IMPOSSIBLE; 

								reOrNot=1;
							}
						}
					}

					if(reOrNot==1)
						j=-1;
					
				}
		}

		if(false)
		{
IMPOSSIBLE:		fout << "Case #" << i << ": " << "IMPOSSIBLE" << "\n";
		}
		else
		{
			fout << "Case #" << i << ": ";
			for(int j=0;j<N;j++)
			{
				fout << milkshakes[j] << " ";
			}
			fout << "\n";
		}
    }

}
