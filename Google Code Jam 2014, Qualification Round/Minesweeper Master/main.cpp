#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>
#include <vector>
#include <iomanip>

using namespace std;

int main()
{
	ifstream fin("C-large-practice.in");
	ofstream fout("C-large-practice.out");

	int cases;
	fin >> cases;
	fin.ignore(1);

	char grid[50][50];

	for (int cas = 1; cas <= cases; cas++)
	{
		int R, C, M;
		fin >> R >> C >> M;

		for (int i = 0; i < 50; ++i)
		for (int k = 0; k < 50; ++k)
		{
			grid[i][k] = '.';
		}

		int succeed = 0;
		if (M == 0)
			succeed = 1;
		else if (M == R*C -1)
		{
			for (int i = 0; i < R; ++i)
			for (int k = 0; k < C; ++k)
			{
				grid[i][k] = '*';
			}
			grid[R - 1][C - 1] = 'c';
			succeed = 1;
		}

		if (succeed == 0 && R == 1)
		{
			while (M > 0)
				grid[0][--M] = '*';
			succeed = 1;
		}
		if (succeed == 0 && C == 1)
		{
			while (M > 0)
				grid[--M][0] = '*';
			succeed = 1;
		}
		if (succeed == 0 && R == 2)
		{
			if (M % 2 == 0 && M < R * C - 2)
			{
				M /= 2;
				while (M > 0)
				{
					grid[0][--M] = '*';
					grid[1][M] = '*';
				}
				succeed = 1;
			}
			else
				succeed = -1;
		}
		if (succeed == 0 && C == 2)
		{
			if (M % 2 == 0 && M < R * C - 2)
			{
				M /= 2;
				while (M > 0)
				{
					grid[--M][0] = '*';
					grid[M][1] = '*';
				}
				succeed = 1;
			}
			else
				succeed = -1;
		}
		if (succeed == 0)
		{
			int pr = 0, pc = 0;
			while (R - pr > 3 && M > 0)
			{
				grid[pr][pc] = '*';
				--M;
				++pc;
				if (pc == C)
				{
					++pr;
					pc = 0;
				}
			}
			if (M == 0)
			{
				succeed = 1;
				if (pc == C - 1)
				{
					grid[pr][pc - 1] = '.';
					grid[pr + 1][0] = '*';
				}
			}
			else
			{
				pc = 0;
				while (C - pc > 3 && M > 0)
				{
					grid[pr][pc] = '*';
					--M;
					++pr;
					if (pr == R)
					{
						pr = R - 3;
						++pc;
					}
				}
				if (M == 0)
				{
					succeed = 1;
					if (pr == R - 1)
					{
						grid[pr - 1][pc] = '.';
						grid[R - 3][pc + 1] = '*';
					}
				}
				else
				{
					if (M > 0)    
					{
						grid[R - 3][C - 3] = '*';
						--M;
						if (M == 0)			 //8
							succeed = 1;
					}

					if (M > 0)		
					{
						grid[R - 3][C - 2] = '*';
						--M;
						if (M == 0)			//7
							succeed = -1;
					}

					if (M > 0)		
					{
						grid[R - 3][C - 1] = '*';
						--M;
						if (M == 0)				//6
							succeed = 1;
					}

					if (M > 0)
					{
						grid[R - 2][C - 3] = '*';
						--M;
						if (M == 0)				//5
							succeed = -1;
					}

					if (M > 0)
					{
						grid[R - 1][C - 3] = '*';
						--M;
						if (M == 0)				//4
							succeed = 1;
					}

					if (M > 0)		
					{
						grid[R - 2][C - 2] = '*';
						--M;
						if (M == 0)				//3
							succeed = -1;
					}

					if (M > 0)	
					{
						grid[R - 2][C - 1] = '*';
						--M;
						if (M == 0)				//2
							succeed = -1;
					}

					if (M > 0)		
					{
						grid[R - 1][C - 2] = '*';
						--M;
						if (M == 0)				//1
							succeed = 1;
					}

					if (M > 0)	
					{
						while (1)
							cout << "error";
					}
				}
			}
		}
		fout << "Case #" << cas << ":";
		
		if (succeed == 1)
		{
			grid[R - 1][C - 1] = 'c';
			for (int i = 0; i < R; ++i)
			{
				fout << "\n";
				for (int k = 0; k < C; ++k)
				{
					fout << grid[i][k];
				}
			}
		}
		else
			fout << "\n" << "Impossible";

		fout << "\n";
	}
	return 0;
}