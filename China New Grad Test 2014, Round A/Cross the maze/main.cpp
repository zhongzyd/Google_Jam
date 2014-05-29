#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>
#include <vector>

using namespace std;

#define loopr(num) (num + 1 == 4? 0 : num + 1)
#define loopl(num) (num - 1 == -1? 3 : num - 1)

vector<vector<char>> maze;
string ans;
int N;

int check(int x, int y, int d)
{
	if(d == 0)
	{
		if(x > 0)
			return maze[x - 1][y];
	}
	if(d == 1)
	{
		if(y < N-1)
			return maze[x][y + 1];
	}
	if(d == 2)
	{
		if(x < N-1)
			return maze[x + 1][y];
	}
	if(d == 3)
	{
		if(y > 0)
			return maze[x][y - 1];
	}
	return 0;
}

void go(int &x, int &y, int d)
{
	if(d == 0)
		x = x - 1;
	if(d == 1)
		y = y + 1;
	if(d == 2)
		x = x + 1;
	if(d == 3)
		y = y - 1;
}

void ansplus(int d)
{
	if(d == 0)
		ans += 'N';
	if(d == 1)
		ans += 'E';
	if(d == 2)
		ans += 'S';
	if(d == 3)
		ans += 'W';
}

int findnextd(int x, int y, int d)
{
	int nextd = loopl(d);
	do
	{
		if(check(x, y, nextd))
			return nextd;
		nextd = loopr(nextd);
	}
	while(nextd != loopl(d));

	return -1;
}


int main()
{
	ifstream fin("D-large-practice.in");
    ofstream fout("D-large-practice.out");

    int cases;
    fin >> cases;
	fin.ignore(1);

    for (int cas = 1; cas <= cases; cas++)
    {
		ans.clear();
		maze.clear();

		fin >> N;
		maze.resize(N);

		for(int i=0;i<N;++i)
		for(int k=0;k<N;++k)
		{
			maze[i].resize(N);
			fin >> maze[i][k];
			if(maze[i][k]=='.')
				maze[i][k] = 1;
			else
				maze[i][k] = 0;
		}

		int sx, sy, ex, ey;
		fin >> sx >> sy >> ex >> ey;

		--sx;
		--sy;
		--ex;
		--ey;
		
		int d=0;

		do
		{
			if(!(check(sx, sy, loopl(d))))
				break;
			d = loopr(d);
		}
		while(true);

		int count = 0;

		while(!(sx == ex && sy == ey) && count <= 10000)
		{
			d = findnextd(sx, sy, d);
			if( d == -1)
			{
				count = -1;
				break;
			}
			go(sx, sy, d);
			ansplus(d);
			++count;
		}

		fout << "Case #" << cas << ": "  ;

		if(count == -1 || count > 10000)
			fout << "Edison ran out of energy." << "\n";
		else
		{
			fout << count << "\n";
			fout << ans << "\n";
		}
    }
    return 0;
}
