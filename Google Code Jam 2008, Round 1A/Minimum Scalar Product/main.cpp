#include <stdio.h>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;
int main()
{
    ifstream fin("A-large-practice.in");
    ofstream fout("A-large-practice.out");

	int T;

    fin >> T;

    for(int i=1;i<=T;++i)
    {
		int n;
		fin >> n;

		vector<long long> v1;
		vector<long long> v2;

		for(int j=0,temp=0;j<n;j++)
		{
			fin>>temp;
			v1.push_back(temp);
		}
		for(int j=0,temp=0;j<n;j++)
		{
			fin>>temp;
			v2.push_back(temp);
		}

		sort(v1.begin(),v1.end());
		sort(v2.begin(),v2.end());

		long long product=0;
		for(int j=0;j<n;j++)
		{
			product += (v1[j]*v2[n-j-1]);
		}

		fout << "Case #" << i << ": " << product << "\n";
    }

}
