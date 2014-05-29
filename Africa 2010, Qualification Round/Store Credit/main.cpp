#include <stdio.h>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;
int main()
{
    ifstream fin("A-large-practice.in");
    ofstream fout("A-large-practice.out");

	int N;

    fin >> N;

    for(int i=1;i<=N;++i)
    {
        int C;
		fin >> C;

		int I;
		fin >>I;

		vector<int> P;

		int temp=0;
		for(int j=0;j<I;++j)
		{
			fin >> temp;
			P.push_back(temp);
		}

		for(int j=0;j<I;++j)
		for(int k=j+1;k<I;++k)
		{
			if( P[j] + P[k] == C )
			{
				fout << "Case #" << i << ": " << j+1 << " " << k+1 << "\n";
				j=I;
				k=I;
				P.clear();
				break;
			}
		}


    }
}
