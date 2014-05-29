#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>
#include <vector>
#include <list>
#include <iomanip>
#include <map>

using namespace std;

int N, D, KK;
int sets[100000][4];

int set_positions[3];
int set_ds[4];

bool TestCover(int i, int k)
{
	int roll;
	for (int j = 0, h; j < D; ++j)
	{
		roll = sets[i][j];
		for (h = 0; h <= k; ++h)
			if (roll == sets[set_positions[h]][set_ds[h]])
				return true;
	}

	return false;
}

int get_max_e_from_s(int s, int k)
{
	set_positions[k] = s;
	int max_e = s + 1; 
	for (int i = 0; i < D; ++i)
	{
		set_ds[k] = i;
		if (*set_positions != 0 && TestCover(*set_positions - 1, k))
			continue;

		int e = s;
		int roll = sets[s][i];

		do
		{
			++e;
			if (e == N)
				return N;
		} while (TestCover(e, k));

		if (k != KK - 1)
			e = get_max_e_from_s(e, k + 1);

		if (e > max_e)
			max_e = e;
	}
	return max_e;
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
		fin >> N >> D >> KK;

		for (int i = 0; i < N; ++i)
		for (int k = 0; k < D; ++k)
			fin >> sets[i][k];

		int max_d = 1;
		int max_s = 0;
		int max_e = 0;
		int s = 0;
		int e = 0;

		while (true)
		{
			if (N - s > max_d)
				e = get_max_e_from_s(s, 0);
			else
				break;

			if (e - s > max_d)
			{
				max_s = s;
				max_e = e - 1;
				max_d = e - s;
			}

			++s;
		}

		fout << "Case #" << cas << ": ";
		fout << max_s << " " << max_e;
		fout << "\n";

		cout << "Case #" << cas << ": ";
		cout << max_s << " " << max_e;
		cout << "\n";
	}
	return 0;
}

/*
int N, D, KK;
int sets[100000][4];


vector<int> ks[2];

int roll_count[100001];
list<int>::iterator roll_ites[100001];
list<int> rolls;

list<int>::iterator ks_check[3] = { rolls.end(), rolls.end(), rolls.end()};

void add_set_count(int i)
{
	for (int d = 0; d < D; ++d)
	{
		int roll = sets[i][d];
		if (roll_count[roll] == 0)
		{
			rolls.push_back(roll);
			roll_ites[roll] = --rolls.end();
		}
		++roll_count[roll];

		list<int>::iterator temp_previous = roll_ites[roll];
		int roll_count_this = roll_count[*roll_ites[roll]];
		list<int>::iterator rolls_begin = rolls.begin();
		while (temp_previous != rolls_begin)
		{
			--temp_previous;
			if (roll_count[*temp_previous] >= roll_count_this)
			{
				++temp_previous;
				break;
			}
		}
		list<int>::iterator temp_this = roll_ites[roll];
		roll_ites[roll] = rolls.insert(temp_previous, *roll_ites[roll]);

		for (int k = 0; k < KK; ++k)
		{
			if (ks_check[k] != rolls.end())
				if (roll_count[*ks_check[k]] < roll_count_this || ks_check[k] == temp_this)
					ks_check[k] = roll_ites[roll];
		}

		rolls.erase(temp_this);
	}
}

void minus_set_count(int i)
{
	for (int d = 0; d < D; ++d)
	{
		int roll = sets[i][d];
		--roll_count[roll];
		if (roll_count[roll] == 0)
		{
			rolls.erase(roll_ites[roll]);
		}
		else
		{
			list<int>::iterator temp_next = roll_ites[roll];
			int roll_count_this = roll_count[*roll_ites[roll]];
			list<int>::iterator rolls_end = rolls.end();

			++temp_next;
			while (temp_next != rolls_end)
			{
				if (roll_count[*temp_next] <= roll_count_this)
					break;
				++temp_next;
			}

			list<int>::iterator temp_this = roll_ites[roll];
			roll_ites[roll] = rolls.insert(temp_next, *roll_ites[roll]);
			rolls.erase(temp_this);
		}
	}
	for (int k = 0; k < KK; ++k)
		ks_check[k] = rolls.end();
}

bool TestCover(int i, int roll)
{
	for (int j = 0; j < D; ++j)
	{
		if (sets[i][j] == roll)
			return true;
	}

	return false;
}

bool Test(int s, int e, int k)
{
	if (k == 0)
	{
		if (ks_check[k] == rolls.end())
		{
			ks_check[k] = rolls.begin();
		}
	}
	else
	{
		if (ks_check[k] == rolls.end())
		{
			ks_check[k] = ks_check[k - 1];
			++ks_check[k];
			if (ks_check[k] == rolls.end())
			{
				if (ks[k - 1].size() == 0)
					return true;
				else
					return false;
			}
		}
	}

	while (ks_check[k] != rolls.end())
	{
		if (k < KK - 1)
		{
			ks[k].clear();
			if (k == 0)
			{
				for (int i = s; i <= e; ++i)
				{
					if (TestCover(i, *ks_check[k]) == false)
						ks[k].push_back(i);
				}
			}
			else
			{
				for (int &i : ks[k - 1])
				{
					if (TestCover(i, *ks_check[k]) == false)
						ks[k].push_back(i);
				}
			}
			if (ks[k].size() == 0)
				return true;

			if (Test(s, e, k + 1) == true)
				return true;
			else
			{
				++ks_check[k];
				if (ks_check[k] == ks_check[k + 1] || ks_check[k] == rolls.end())
					return false;
			}
		}
		else
		{
			int cover_count = 0;
			for (int i = 0; i < KK; ++i)
			{
				if (ks_check[i] != rolls.end())
					cover_count += roll_count[*ks_check[i]];
			}
			if (cover_count < e + 1 - s)
				return false;

			int i = 0;
			int ks_size = ks[k - 1].size();
			for (; i < ks_size; ++i)
			{
				if (TestCover(ks[k - 1][i], *ks_check[k]) == false)
				{
					++ks_check[k];
					break;
				}
			}
			if (i == ks_size)
				return true;
		}
	}

	return false;
}

int main()
{
	for (int i = 0; i < 2; ++i)
		ks[i].reserve(100000);

	ifstream fin("D-small-practice.in");
	ofstream fout("D-small-practice.out");

	int cases;
	fin >> cases;
	fin.ignore(1);

	for (int cas = 1; cas <= cases; cas++)
	{
		memset(roll_count, 0, sizeof(roll_count));
		rolls.clear();
		for (int k = 0; k < KK; ++k)
			ks_check[k] = rolls.end();

		fin >> N >> D >> KK;

		for (int i = 0; i < N; ++i)
		for (int k = 0; k < D; ++k)
			fin >> sets[i][k];

		int max_d = 1;
		int max_s = 0;
		int max_e = 0;
		int s = 0;
		int e = 0;

		add_set_count(0);
		
		while (e < N && N - s > max_d)
		{
			while (e < N && Test(s, e, 0))
			{
				++e;
				add_set_count(e);
			}

			ks;

			roll_count;
			roll_ites;
			rolls;

			ks_check;



			if (e - s > max_d)
			{
				max_s = s;
				max_e = e - 1;
				max_d = e - s;
			}

			minus_set_count(s);
			++s;
		}

		fout << "Case #" << cas << ": ";
		fout << max_s << " " << max_e;
		fout << "\n";

		cout << "Case #" << cas << ": ";
		cout << max_s << " " << max_e;
		cout << "\n";
	}
	return 0;
}
*/