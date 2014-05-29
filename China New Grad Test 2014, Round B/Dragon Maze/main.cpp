#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>
#include <vector>
#include <iomanip>

using namespace std;

vector<vector<int>> maze;
int N;
int M;

struct Point
{
	int x;
	int y;
	int power;
	int accumulated_power;

	bool operator == (Point p2)
	{
		if(x == p2.x && y == p2.y)
			return true;
		else
			return false;
	}

	bool operator < (Point p2)
	{
		return accumulated_power < p2.accumulated_power;
	}

	Point operator + (Point p2)
	{
		Point p;
		p.x = p2.x;
		p.y = p2.y;
		p.accumulated_power = accumulated_power + p2.power;
		return p;
	}
};

int GetPower(Point p)
{
	if(p.x >= 0 && p.x < N && p.y >= 0 && p.y < M)
	{
		int temp = maze[p.x][p.y];
		maze[p.x][p.y] = -1;
		return temp;
	}
	else
		return -1;
}

Point GetPoint(Point p, string s)
{
	if(s == "up")
		p.x -= 1;
	else if(s == "right")
		p.y += 1;
	else if(s == "down")
		p.x += 1;
	else if(s == "left")
		p.y -= 1;

	p.power = GetPower(p);
	return p;
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
		fin >> N >> M;
		
		Point entrance;
		fin >> entrance.x;
		fin >> entrance.y;
		
		Point exit;
		fin >> exit.x;
		fin >> exit.y;

		maze.resize(N);
		for(int i = 0; i < N; ++i)
		{
			maze[i].resize(M);
			for(int k = 0; k < M; ++k)
			{
				fin >> maze[i][k];
			}
		}

		entrance.accumulated_power = GetPower(entrance);

		vector<Point> ps;
		ps.push_back(entrance);

		vector<Point> ps1;
		Point p;
		while(!ps.empty())
		{
			if(find(ps.begin(), ps.end(), exit) != ps.end())
				break;

			while(!ps.empty())
			{
				p = GetPoint(ps.back(), "up");
				if(p.power >= 0)
					ps1.push_back(ps.back() + p);
	
				p = GetPoint(ps.back(), "right");
				if(p.power >= 0)
					ps1.push_back(ps.back() + p);

				p = GetPoint(ps.back(), "down");
				if(p.power >= 0)
					ps1.push_back(ps.back() + p);

				p = GetPoint(ps.back(), "left");
				if(p.power >= 0)
					ps1.push_back(ps.back() + p);

				ps.pop_back();
			}

			ps = ps1;
			sort(ps.begin(), ps.end());
			ps1.clear();
		}

        fout << "Case #" << cas << ": "  ;

		if(ps.size() > 0)
			fout << find(ps.begin(), ps.end(), exit)->accumulated_power;
		else
			fout << "Mission Impossible.";

		fout << "\n";
    }
    return 0;
}