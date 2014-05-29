#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>
#include <vector>

using namespace std;

int main()
{
	ifstream fin("A-large-practice.in");
    ofstream fout("A-large-practice.out");

    int cases;
    fin >> cases;
	fin.ignore(1);

	char pictures[50][50];
    for (int cas = 1; cas <= cases; cas++)
    {
		int R;
		int C;
		fin >> R >> C;

		for(int i=0; i < R; ++i)
	    for(int j=0; j < C; ++j)
		{
			fin >> pictures[i][j];
		}

		bool flag = true;
		for(int i=0; i < R; ++i)
	    for(int j=0; j < C; ++j)
		{
			if(pictures[i][j] == '#')
			{
				pictures[i][j] = '/';
				if(j + 1 < C && pictures[i][j + 1] == '#')
				{
					pictures[i][j + 1] = '\\';
				}
				else
					flag = false;

				if(i + 1 < R && pictures[i + 1][j] == '#')
				{
					pictures[i + 1][j] = '\\';
				}
				else
					flag = false;

				if(i + 1 < R && j + 1 < C && pictures[i + 1][j + 1] == '#')
				{
					pictures[i + 1][j + 1] = '/';
				}
				else
					flag = false;
			}
		}

		fout << "Case #" << cas << ": " << "\n";
		if (flag == true)
		{
			for(int i=0; i < R; ++i)
			{
				for(int j=0; j < C; ++j)
				{
					fout << pictures[i][j];
				}
				fout << "\n";
			}
		}
		else
           fout << "Impossible"  << "\n";
    }
    return 0;
}
