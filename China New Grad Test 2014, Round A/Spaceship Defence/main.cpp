#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>
#include <vector>
#include <map>
using namespace std;

#define INFINITE 999999999

int main()
{
	ifstream fin("E-small-practice.in");
    ofstream fout("E-small-practice.out");

    int cases;
    fin >> cases;
	fin.ignore(1);

    for (int cas = 1; cas <= cases; cas++)
    {
		int N;
		fin >> N;

		vector<string> colors;
		colors.resize(N);

		for(int i = 0; i < N; ++i)
		{
			fin >> colors[i];
		}
		
		map<string, int> colors_map;

		for(int i = 0, k = 0; i < N; i++)
		{
			if(colors_map.count(colors[i]) == 0)
				colors_map[colors[i]] = k++;
		}

		int M;

		fin >> M;
		
		vector<vector<int>> turbolifts;
		turbolifts.resize(M);
		
		for(int i = 0; i < M; ++i)
		{
			turbolifts[i].resize(3);
			fin >> turbolifts[i][0];
			--turbolifts[i][0];
			fin >> turbolifts[i][1];
			--turbolifts[i][1];
			fin >> turbolifts[i][2];
		}
		
		int S;

		fin >> S;

		vector<vector<int>> soldiers;
		soldiers.resize(S);
		
		for(int i = 0; i < S; ++i)
		{
			soldiers[i].resize(2);
			fin >> soldiers[i][0];
			--soldiers[i][0];
			fin >> soldiers[i][1];
			--soldiers[i][1];
		}

		int colors_map_size = colors_map.size();
		vector<vector<int>> distance;

		distance.resize(colors_map_size);
		for(int i = 0; i < colors_map_size; ++i)
		{
			distance[i].resize(colors_map_size);
			for(int j = 0; j < colors_map_size; ++j)
			{
				if(i == j)
					distance[i][j] = 0;
				else
					distance[i][j] = INFINITE;
			}
		}

		for(int i = 0; i < M; ++i)
		{
			int fromroom = turbolifts[i][0];
			int toroom = turbolifts[i][1];
			int fromcolor = colors_map[colors[fromroom]];
			int tocolor = colors_map[colors[toroom]];
			distance[fromcolor][tocolor] = min(distance[fromcolor][tocolor], turbolifts[i][2]);
		}

		for(int k = 0; k < colors_map_size; ++k)
		for(int i = 0; i < colors_map_size; ++i)
		for(int h = 0; h < colors_map_size; ++h)
		{
			if(distance[i][h] > distance[i][k] + distance[k][h])
			{
				distance[i][h] = distance[i][k] + distance[k][h];
			}
		}

        fout << "Case #" << cas << ": "  <<"\n";

		for(int i = 0; i < S; ++i)
		{
			if( distance[colors_map[colors[soldiers[i][0]]]][colors_map[colors[soldiers[i][1]]]] == INFINITE )
				fout << -1 << "\n";
			else
				fout << distance[colors_map[colors[soldiers[i][0]]]][colors_map[colors[soldiers[i][1]]]] << "\n";
		}
    }
    return 0;
}
