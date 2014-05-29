#include <stdio.h>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

long long AB[1000001];
vector<int> prime;

void get_prime()
{
		int *Num=new int[1000001];

		for(int i=0;i<1000001;i++)
		{
			Num[i]=1;
		}

		prime.reserve(1000001);
		for(int i = 2; i < 1000001 ; ++i)
		{
			if(Num[i]==1)
			{
				prime.push_back(i);
				for(long long j = (long long)i * i; j < 1000001; j += i)
				{
					Num[j]=0;
				}
			}
		}
}

int root(int x)
{
	if( AB[x] < 0)
		return x;
	else
		return AB[x] = root(AB[x]);
}

void merge(int a, int b)
{
	a = root(a);
	b = root(b);
	if(a == b)
		return;
	if(AB[a] > AB[b])
		swap(a, b);
	AB[a] += AB[b];
	AB[b] = a;
}

int main()
{
    ifstream fin("B-large-practice.in");
    ofstream fout("B-large-practice.out");
	
	int cases;

    fin >> cases;
	fin.ignore(1);

	get_prime();
	
    for(int cas = 1; cas <= cases; cas++)
    { 
		long long A;
		long long B;
		long long P;
		fin >> A;
		fin >> B;
		fin >> P;

		for(long long i = 0; i <= B - A; ++i)
		{
			AB[i]=-1;
		}

		long long low = prime.size();
		int prime_size = prime.size();
		for(int i = 0 ; i < prime_size; ++i)
		{
			if(prime[i] >= P)
			{
				low = i;
				break;
			}
		}

		for(long long i = low; i < prime_size && prime[i] <= B - A; ++i)
		{
			long long t = B - B % prime[i];

			int this_prime=prime[i];
			while(t - this_prime >= A)
			{
				merge(t - A, t - this_prime - A);
				t -= this_prime;
			}
		}

		int count = 0;
		for(int i = 0; i <= B - A; ++i)
		{
			if(AB[i] < 0)
				count++;
		}

		fout << "Case #" << cas << ": " << count <<"\n";
    }
}
