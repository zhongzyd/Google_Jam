#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>
#include <vector>
#include <iomanip>

using namespace std;


int num(string &s, int i)
{
	if (i == s.size())
		return 0;
	int t = i + 1;
	while (t < s.size())
	{
		if (s[i] == s[t])
			++t;
		else
			break;
	}
	return t - i;
}

int find_l(vector<int> &c)
{
	int k = c[0];
	for (int d = 0; d < c.size(); ++d)
	{
		if (c[d] < k)
			k = c[d];
	}
	return k;
}

int find_h(vector<int> &c)
{
	int k = c[0];
	for (int d = 0; d < c.size(); ++d)
	{
		if (c[d] > k)
			k = c[d];
	}
	return k;
}

int nonnegative(int c1, int c2)
{
	if (c1 > c2)
		return c1 - c2;
	else
		return c2 - c1;
}

int cal_distance(vector<int> &c, int k)
{
	int distance = 0;
	for (int t = 0; t < c.size(); ++t)
		distance += nonnegative(c[t], k);
	return distance;
}

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
		vector<string> s;
		s.resize(N);
		for (int k = 0; k < N; ++k)
			fin >> s[k];

		vector<int> i;
		i.resize(N);
		for (int k = 0; k < N; ++k)
		{
			i[k] = 0;
		}
		
		vector<int> c;
		c.resize(N);

		int succeed = 0;
		int cal = 0;
		while (true)
		{
			for (int k = 0; k < N - 1; ++k)
				if (s[k][i[k]] != s[k + 1][i[k + 1]])
					goto end;

			for (int k = 0; k < N; ++k)
				c[k] = num(s[k], i[k]);

			int smallest = 999999;
			int l = find_l(c);
			int h = find_h(c);
			int distance;
			for (int k = l; k <= h; ++k)
			{
				distance = cal_distance(c, k);
				if (distance < smallest)
					smallest = distance;
			}
			cal += smallest;

			int e = 0;
			for (int k = 0; k < N; ++k)
			{
				i[k] += c[k];
				if (i[k] == s[k].size())
					e = 1;
			}

			if (e == 1)
			{
				for (int k = 0; k < N; ++k)
				{
					if (i[k] != s[k].size())
						goto end;
				}
				succeed = 1;
				goto end;
			}

		}
end:
		fout << "Case #" << cas << ": ";
		if (succeed == 1)
			fout << cal;
		else
			fout << "Fegla Won";
		fout << "\n";
	}
	return 0;
}