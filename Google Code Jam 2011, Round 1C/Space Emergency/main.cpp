#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>
#include <vector>
#include <map>
#include <queue>

using namespace std;

int main()
{
	ifstream fin("B-large-practice.in");
    ofstream fout("B-large-practice.out");

    long long cases;
    fin >> cases;
	fin.ignore(1);
	
	for (long long cas = 1; cas <= cases; cas++)
    {
		long long L, t, N, C;
		fin >> L >> t >> N >> C;

		long long *a = new long long[C];
		for(long long i = 0; i < C; ++i)
			fin >> a[i];

		long long *time_each = new long long[N];

		for(long long i = 0; i < N; )
		{
			for(long long j = 0; j < C && i < N; ++j, ++i)
			{
				time_each[i] = a[j]*2;
			}
		}

		priority_queue<long long> time_each_priority;
		long long time_sum = 0;

		long long i = 0;
		while(i < N)
		{
			if(t - time_each[i] < 0)
			{
				time_sum += t;
				time_each_priority.push(time_each[i++] - t);
				while(i<N)
					time_each_priority.push(time_each[i++]);
			}
			else
			{
				time_sum += time_each[i];
				t -= time_each[i++];
			}
		}

		while(time_each_priority.size() > 0)
		{
			if(L > 0)
			{
				time_sum += time_each_priority.top()/2;
				--L;
			}
			else
				time_sum += time_each_priority.top();

			time_each_priority.pop();
		}
		

	/*
    for (long long cas = 1; cas <= cases; cas++)
    {
		long long L, t, N, C;
		fin >> L >> t >> N >> C;

		long long *a = new long long[C];
		for(long long i = 0; i < C; ++i)
			fin >> a[i];

		long long *time_each = new long long[N];

		for(long long i = 0; i < N; )
		{
			for(long long j = 0; j < C && i < N; ++j, ++i)
			{
				time_each[i] = a[j]*2;
			}
		}

		multimap<long long, long long> distancemap;
		multimap<long long, long long>::iterator it;
		for(long long i = 0; i < C; ++i)
		{
			distancemap.insert(pair<long long, long long>(time_each[i],i));
		}

		long long time_sum = 0;
		long long pos = 0;
		bool flag = false;
		bool flag1 = false;
		for(long long i = 0; i < N; )
		{
			if(flag1)
			{
				time_sum += time_each[i++];
			}
			else if(t - time_each[i] < 0)
			{
				flag1 = true;
				std::map<long long,long long>::reverse_iterator ittemp;
				for (std::map<long long,long long>::reverse_iterator it = distancemap.rbegin(); it != distancemap.rend() && L > 0; ++it)
				{
					if( flag == false && time_each[i] - t > it->first)
					{
						time_each[i] =  time_each[i] - (time_each[i] - t) / 2;
						--L;

						t = 0;

						flag = true;
					}

					long long j = i / C * C + it->second;
					if( j <= i )
						j += C;
					while( j < N && L > 0)
					{
						time_each[j] /= 2;
						--L;
						j += C;
					}
					

					ittemp = it;
					++ittemp;
					if( flag == false && ittemp == distancemap.rend())
					{
						time_each[i] =  time_each[i] - (time_each[i] - t) / 2;
						--L;

						t = 0;

						flag = true;
					}
				}
			}
			else
			{
				time_sum += time_each[i];
				t -= time_each[i++];
			}

		}
		*/

	/*	
	long long loopsum = 0;
		for(long long i = 0; i < C; ++i)
			loopsum += a[i];

		loopsum *= 2;
	
	long long loop_count1 = t / loopsum;
		long long loop_pos = 0;
		for(long long count = 0; loop_pos < C; ++loop_pos)
		{
			count += a[loop_pos]*2;
			if(count > t - loop_count1 * loopsum)
				break;
		}

		long long time_sum = 0;
		time_sum += N / C * loopsum;
		for(long long i = N; i > N / C * C; ++i)
		{
			time_sum += a[N - i];
		}

		long long 
	*/
        fout << "Case #" << cas << ": "  << time_sum << "\n";
    }
    return 0;
}
