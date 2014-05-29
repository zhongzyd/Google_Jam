#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>
#include <vector>
#include <iomanip>
#include <time.h>
#include <set>

using namespace std;

struct jump
{
	int clearing;
	int a_state;
	int count;
};

int main()
{
	ifstream fin("E-large-practice.in");
    ofstream fout("E-large-practice.out");

    int cases;
    fin >> cases;
	fin.ignore(1);

    for (int cas = 1; cas <= cases; cas++)
    {
		int N;
		fin >> N;

		--N;

		int paths[39][2];

		for(int i = 0; i < N; ++i)
		{
			fin >> paths[i][0];
			--paths[i][0];

			fin >> paths[i][1];
			--paths[i][1];
		}

		vector<int> a;
		vector<int> s;

		s.push_back(0);

		while(a.size() < N / 2 && s.size() > 0)
		{
			if(s[0] == N)
			{
				s.erase(s.begin());
				continue;
			}

			a.push_back(s[0]);
			s.erase(s.begin());

			for(int i = 0; i < 2; ++i)
			{
				if(find(a.begin(), a.end(), paths[a.back()][i]) == a.end())
					if(find(s.begin(), s.end(), paths[a.back()][i]) == s.end())
						s.push_back(paths[a.back()][i]);
			}
		}

		int ib = 0;
		int ie = N - 1;
		while(true)
		{
			while(find(a.begin(), a.end(), ib) != a.end() && ib < ie)
				++ib;

			while(find(a.rbegin(), a.rend(), ie) == a.rend() && ib < ie)
				--ie;

			if(ib >= ie)
				break;

			swap(paths[ib][0],paths[ie][0]);
			swap(paths[ib][1],paths[ie][1]);

			for(int i = 0;i < N; ++i)
			for(int k = 0;k < 2; ++k)
			{
				if(paths[i][k] == ib)
					paths[i][k] = ie;
				else if(paths[i][k] == ie)
					paths[i][k] = ib;
			}
			++ib;
			--ie;
		}

		int a_size = a.size();	
		
		vector<vector<jump>> as;
		as.resize(a_size);
		for(int i = 0; i < a_size; ++i)
		{
			as[i].resize(1 << a_size);
			for(int k = 0; k < 1 << a_size; ++k)
				as[i][k].clearing = -1;
		}

		s.clear();
		s.push_back(N);
		vector<int> live_clearing;
		while(s.size() > 0)
		{
			live_clearing.push_back(s[0]);
			s.erase(s.begin());

			for(int i = 0; i < N; ++i)
			for(int k = 0; k < 2; ++k)
			{
				if(paths[i][k] == live_clearing.back())
				{
					if(find(live_clearing.begin(), live_clearing.end(), i) == live_clearing.end())
					if(find(s.begin(), s.end(), i) == s.end())
						s.push_back(i);
				}
			}
		}

		set<int> dead_clearing;
		for(int i = 0; i < N; ++i)
			dead_clearing.insert(i);

		for(int i = 0; i < live_clearing.size(); ++i)
			dead_clearing.erase(live_clearing[i]);

		long long count = 0;
		int clearing = 0;
		long long state = 0;
		int a_mask = (1 << a_size) - 1;
		long long max_count = N * (1LL << N) + 2;
		int a_max_count = a_size * (1 << a_size) + 2;
		int b_max_count = (N - a_size) * (1 << (N - a_size)) + 2;
		int a_count = 0;
		int b_count = 0;
		while(count < max_count)
		{
			if(clearing  < a_size)
			{
				b_count = 0;
				int a_state = state & (long long)a_mask;
				if(as[clearing][a_state].clearing == -1)
				{
					int a_clearing = clearing;
					vector<int> a_clearings;
					vector<int> a_states;
					do
					{
						a_clearings.push_back(a_clearing);
						a_states.push_back(a_state);

						int left_right = (a_state >> a_clearing) & 1;
						a_state ^= 1 << a_clearing;
						a_clearing = paths[a_clearing][left_right];

						++a_count;

						if(dead_clearing.count(a_clearing) == 1)
						{
							count = max_count + 1;
							break;
						}

						if(a_count > a_max_count)
						{
							count = max_count + 1;
							break;
						}
					}
					while(a_clearing < a_size);

					int b_clearing = a_clearing;

					if(count < max_count)
					while(a_clearings.size() > 0)
					{
						as[a_clearings.back()][a_states.back()].clearing = b_clearing;
						as[a_clearings.back()][a_states.back()].a_state = a_state;
						as[a_clearings.back()][a_states.back()].count = a_count - a_clearings.size() + 1;
						a_clearings.pop_back();
						a_states.pop_back();
					}
				}

				if(count < max_count)
				{
					a_state = state & (long long)a_mask;
					count += as[clearing][a_state].count;
					state = (state & ~(long long)a_mask) | (long long)as[clearing][a_state].a_state;
					clearing = as[clearing][a_state].clearing;
				}
			}
			else
			{
				a_count = 0;
				int left_right = (state >> clearing) & 1;
				state ^= 1LL << clearing;
				clearing = paths[clearing][left_right];

				if(dead_clearing.count(clearing) == 1)
					count = max_count + 1;

				++b_count;
				if(b_count > b_max_count)
					count = max_count + 1;

				++count;
			}
				
			if(clearing == N)
				break;
		}


        fout << "Case #" << cas << ": "  ;

		if(clearing == N)
			fout << count;
		else
			fout << "Infinity";

		fout << "\n";
    }
    return 0;
}