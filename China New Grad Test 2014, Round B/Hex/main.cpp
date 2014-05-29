#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>
#include <vector>
#include <iomanip>

using namespace std;

int N;
int board[100][100];
int board_backup[100][100];
vector<int> bfs_x;
vector<int> bfs_y;

int flag_win = 0;

int TestAndPush(int x, int y, int color)
{
	if(color == 1)
	{
		if(y >= 0 && y < N)
		{
			if(x >= 0 && x <= N)
			{
				if(x < N && board[x][y] == color)
				{
					bfs_x.push_back(x);
					bfs_y.push_back(y);
					board[x][y] = -color;
					return 1;
				}
				else if(x == N)
				{
					flag_win = 1;
					return 0;
				}
			}
		}
	}
	else if(color == 2)
	{
		if(x >= 0 && x < N)
			if(y >= 0 && y <= N)
			{
				if(y < N && board[x][y] == color)
				{
					bfs_x.push_back(x);
					bfs_y.push_back(y);
					board[x][y] = -color;
					return 1;
				}
				else if(y == N)
				{
					flag_win = 1;
					return 0;
				}
			}
	}
	return 0;
}

int PushNeighbor(int color)
{
	int x = bfs_x.back();
	int y = bfs_y.back();

	int return_state = 0;
	int test_x;
	int test_y;

	test_x = x;
	test_y = y - 1;
	return_state += TestAndPush(test_x, test_y, color);

	test_x = x + 1;
	test_y = y - 1;
	return_state += TestAndPush(test_x, test_y, color);

	test_x = x - 1;
	test_y = y;
	return_state += TestAndPush(test_x, test_y, color);

	test_x = x + 1;
	test_y = y;
	return_state += TestAndPush(test_x, test_y, color);

	test_x = x;
	test_y = y + 1;
	return_state += TestAndPush(test_x, test_y, color);

	test_x = x - 1;
	test_y = y + 1;
	return_state += TestAndPush(test_x, test_y, color);

	return return_state;
}

int FindInitialPush(int color)
{
	for(int i = 0; i < N; ++i)
	{
		int x = (color - 1) * i;
		int y = (2 - color) * i;
		if(board[x][y] == color)
		{
			bfs_x.push_back(x);
			bfs_y.push_back(y);
			board[x][y] = -color;
		}
	}
	return 0;
}

void ReSetBoard()
{
	for(int i = 0; i < N; ++i)
		memcpy(board[i], board_backup[i], sizeof(int) * N); 
}

void TestWin(int color)
{
	flag_win = 0;
	int neighbor_num;
	FindInitialPush(color);
	while(!bfs_x.empty())
	{
		neighbor_num = PushNeighbor(color);
		if(neighbor_num <= 0)
		{
			bfs_x.pop_back();
			bfs_y.pop_back();
		}
	}
	ReSetBoard();
}

int TestTrueWin(int color)
{
	TestWin(color);
	if(flag_win)
	{
		for(int i = 0; i < N; ++i)
		for(int k = 0; k < N; ++k)
		{
			if(board[i][k] == color)
			{
				board[i][k] = -color;
				TestWin(color);

				if(!flag_win)
				{
					flag_win = 1;
					return color;
				}
			}
		}
		return -1;
	}
	return 0;
}

int main()
{
	ifstream fin("C-large-practice.in");
    ofstream fout("C-large-practice.out");

    int cases;
    fin >> cases;
	fin.ignore(1);

    for (int cas = 1; cas <= cases; cas++)
    {
		fin >> N;

		int r_count = 0;
		int b_count = 0;
		for(int x = 0; x < N; ++x)
		for(int y = 0; y < N; ++y)
		{
			char c;
			fin >> c;
			if(c == '.')
				board[x][y] = 0;
			else if(c == 'R')
			{
				++r_count;
				board[x][y] = 1;
			}
			else if(c == 'B')
			{
				++b_count;
				board[x][y] = 2;
			}
		}
		
		for(int i = 0; i < N; ++i)
			memcpy(board_backup[i], board[i], sizeof(int) * N); 

		int state = 0;
		if(abs(r_count - b_count) > 1)
			state = -1;

		if(state == 0)
		{
			int color = 1;
			state = TestTrueWin(color);
			if(state == 1)
			{
				if(b_count > r_count)
					state = -1;
			}
		}

		if(state == 0)
		{
			int color = 2;
			state = TestTrueWin(color);
			if(state == 2)
			{
				if(r_count > b_count)
					state = -1;
			}
		}
		

        fout << "Case #" << cas << ": "  ;

		if(state == -1)
		{
			fout << "Impossible" ;
		}
		else if(state == 0)
		{
			fout << "Nobody wins";
		}
		else if(state == 1)
		{
			fout << "Red wins";
		}
		else if(state == 2)
		{
			fout << "Blue wins";
		}

		fout << "\n";
    }
    return 0;
}