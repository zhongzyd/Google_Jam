#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>
#include <vector>
#include <iomanip>

using namespace std;

int main()
{
	ifstream fin("A-large.in");
    ofstream fout("A-large.out");

    int cases;
    fin >> cases;
	fin.ignore(1);

    for (int cas = 1; cas <= cases; cas++)
    {
		int N;
		fin >> N;
		vector<vector<int>> matrix;

		matrix.resize(N * N);
		for(int i = 0; i < N * N; ++i)
		{
			matrix[i].resize(N * N);
			for(int k = 0; k < N * N; ++k)
				fin >> matrix[i][k];
		}

		int test[1001];
		
		int flag = true;
		for(int i = 0; i < N * N; ++i)
		{
			memset(test, 0, 1001 * sizeof(int));
			for(int k = 0; k < N * N; ++k)
			{
				test[matrix[i][k]] = 1;
			}
			for(int h = 1; h <= N * N; ++h)
			{
				if(test[h] != 1)
				{
					flag = false;
					goto answer;
				}
			}
		}

		for(int i = 0; i < N * N; ++i)
		{
			memset(test, 0, 1001 * sizeof(int));
			for(int k = 0; k < N * N; ++k)
			{
				test[matrix[k][i]] = 1;
			}
			for(int h = 1; h <= N * N; ++h)
			{
				if(test[h] != 1)
				{
					flag = false;
					goto answer;
				}
			}
		}

		for(int i = 0; i < N; ++i)
		{
			for(int k = 0; k < N; ++k)
			{
				memset(test, 0, 1001 * sizeof(int));
				for(int g = 0; g < N; ++g)
				{
					for(int f = 0; f < N; ++f)
						test[matrix[N * i + g][N * k + f]] = 1;
				}

				for(int h = 1; h <= N * N; ++h)
				{
					if(test[h] != 1)
					{
						flag = false;
						goto answer;
					}
				}
			}
			
		}


answer: 
		fout << "Case #" << cas << ": "  ;

		if(flag == true)
			fout << "Yes";
		else
			fout << "No";

		fout << "\n";
    }
    return 0;
}