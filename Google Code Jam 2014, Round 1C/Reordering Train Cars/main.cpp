#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>
#include <vector>
#include <iomanip>
#include <list>

using namespace std;

typedef struct int2
{
	int a;
	int b;
}INT2;

int main()
{
	ifstream fin("B-large-practice.in");
	ofstream fout("B-large-practice.out");

	int cases;
	fin >> cases;
	fin.ignore(1);

	vector<string> vs;
	vs.resize(100);
	list<INT2> vi;
	int ch[256];
	int count[256];
	for (int cas = 1; cas <= cases; cas++)
	{
		vi.clear();
		int N;
		fin >> N;
		for (int i = 0; i < N; ++i)
		{
			vs[i].clear();
			fin >> vs[i];
		}

		int succeed = 0;
		for (int i = 0; i < N; ++i)
		{
			char a = vs[i][0];
			char b = vs[i][vs[i].size()-1];
			for (int k = 0; k < vs[i].size(); ++k)
			{
				if (vs[i][k] != a && vs[i][k] != b)
				{
					for (int h = 0; h < N; ++h)
					{
						if (h != i)
						for (int q = 0; q < vs[h].size(); ++q)
						{
							if (vs[i][k] == vs[h][q])
								goto fail;
						}
					}
				}
			}
		}

		for (int i = 0; i < N; ++i)
		{
			memset(ch, 0, 256 * sizeof(int));
			char a;
			for (int k = 0; k < vs[i].size();)
			{
				a = vs[i][k];
				if (ch[a] != 1)
					ch[a] = 1;
				else
					goto fail;
				while (k < vs[i].size())
				{
					if (vs[i][k] == a)
						++k;
					else
						break;
				}
			}
		}

		for (int i = 0; i < N; ++i)
		{
			INT2 temp;
			temp.a = vs[i][0];
			temp.b = vs[i][vs[i].size() - 1];
			vi.push_back(temp);
		}

		
		memset(count, 0, 256 * sizeof(int));
		for (list<INT2>::iterator i = vi.begin(); i != vi.end();)
		{
			if (i->a == i->b)
			{
				++count[i->a];
				list<INT2>::iterator temp = i;
				++i;
				vi.erase(temp);
			}
			else
				++i;
		}

		long long answer = 1;
		while (true)
		{
re:
			for (list<INT2>::iterator i = vi.begin(); i != vi.end(); ++i)
			{
				for (list<INT2>::iterator k = vi.begin(); k != vi.end(); ++k)
				{
					if (k != i)
					{
						if (i->b == k->a)
						{
							for (list<INT2>::iterator q = vi.begin(); q != vi.end(); ++q)
							{
								if (q != i && q != k)
								{
									if (q->a == i->b || q->b == i->b)
										goto fail;
								}
							}
							if (count[i->b] != 0)
							{
								while (count[i->b] > 0)
								{
									answer *= count[i->b];
									answer %= 1000000007;
									--count[i->b];
								}
							}
							count[i->b] = 0;
							INT2 temp;
							temp.a = i->a;
							temp.b = k->b;
							vi.push_back(temp);
							vi.erase(i);
							vi.erase(k);
							goto re;
						}
					}
				}
			}
			break;
		}

		memset(ch, 0, 256 * sizeof(int));
		for (list<INT2>::iterator i = vi.begin(); i != vi.end(); ++i)
		{
			if (ch[i->a] != 0)
				goto fail;
			else
				++ch[i->a];

			if (ch[i->b] != 0)
				goto fail;
			else
				++ch[i->b];
		}

		long long A = vi.size();
		for (int i = 'a'; i <= 'z'; ++i)
		{
			if (count[i] != 0)
			{
				for (list<INT2>::iterator k = vi.begin(); k != vi.end(); ++k)
				{
					if (k->a == i || k->b == i)
					{
						--A;
						break;
					}
				}
				++A;
				while (count[i] > 0)
				{
					answer *= count[i];
					answer %= 1000000007;
					--count[i];
				}
			}
		}

		while (A > 0)
		{
			answer *= A;
			answer %= 1000000007;
			--A;
		}
		succeed = 1;

fail:
		fout << "Case #" << cas << ": ";

		if (succeed == 0)
			fout << 0;
		else
			fout << answer;

		fout << "\n";
	}
	return 0;
}