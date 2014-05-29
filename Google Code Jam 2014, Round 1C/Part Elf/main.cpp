#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>
#include <vector>
#include <iomanip>

using namespace std;

long long GCD(long long a, long long b)
{
	if (b == 0)
		return a;
	return GCD(b, a % b);
}

int main()
{
	ifstream fin("A-large.in");
	ofstream fout("A-large.out");

	int cases;
	fin >> cases;
	fin.ignore(1);

	long long p240 = 1;
	for (long long i = 0; i < 40; ++i)
		p240 *= 2L;

	for (int cas = 1; cas <= cases; cas++)
	{
		long long P, Q;
		fin >> P;
		char temp;
		fin >> temp;
		fin >> Q;

		int succeed = 0;
		long long answer = 40;

		long long gcd = GCD(P, Q);
		P /= gcd;
		Q /= gcd;
		
		if (p240 % Q == 0)
		{
			P *= (p240 / Q);
			
			while (P > 1)
			{
				P /= 2L;
				--answer;
			}
			succeed = 1;
		}


		fout << "Case #" << cas << ": ";
		if (succeed == 0)
			fout << "impossible";
		else
			fout << answer;
		fout << "\n";
	}
	return 0;
}