#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>
#include <vector>
#include <iomanip>

using namespace std;

long long get_answer(long long A, long long  B, long long K, long long i);

long long get_answer000(long long A, long long  B, long long K, long long i)
{
	long long ans = get_answer(A, B, K, i >> 1);
	return ans;
}

long long get_answer100(long long A, long long  B, long long K, long long i)
{
	long long ans = get_answer(i - 1, B, K, i >> 1) + get_answer(A & (i - 1), B, K, i >> 1);
	return ans;
}

long long get_answer010(long long A, long long  B, long long K, long long i)
{
	long long ans1 = get_answer(A, i - 1, K, i >> 1);
	long long ans2 = get_answer(A, B & (i - 1), K, i >> 1);
	return ans1 + ans2;
}

long long get_answer110(long long A, long long  B, long long K, long long i)
{
	long long ans = get_answer(i - 1, i - 1, K, i >> 1) + get_answer(i - 1, B & (i - 1), K, i >> 1)
												+ get_answer(A & (i - 1), i - 1, K, i >> 1);
	return ans;
}


long long get_answer(long long A, long long  B, long long K, long long i)
{
	if (i == 1)
	{
		int answer = 0;
		K &= 1;
		for (int a = 0; a <= A; ++a)
		for (int b = 0; b <= B; ++b)
		{
			if ((a & b) <= K)
				++answer;
		}
		return answer;
	}
	else
	{
		long long a = A & i;
		long long b = B & i;
		long long k = K & i;
		if (k == 0)
		{
			if (a == 0 && b == 0)
			{
				long long ans = get_answer000(A, B, K, i);
				return ans;
			}
			else if (a > 0 && b == 0)
			{
				long long ans = get_answer100(A, B, K, i);
				return ans;
			}
			else if (a == 0 && b > 0)
			{
				long long ans = get_answer010(A, B, K, i);
				return ans;
			}
			else if (a > 0 && b > 0)
			{
				long long ans = get_answer110(A, B, K, i);
				return ans;
			}
		}
		else if ( k > 0 )
		{
			long long a = A & i;
			long long b = B & i;

			if (a > 0 && b > 0)
			{
				long long ans = i * i + ((A & (i - 1)) + 1) * i + i * ((B & (i - 1)) + 1) + get_answer(A & (i - 1), B & (i - 1), K, i >> 1);
				return ans;
			}
			else
			{
				long long ans = (A + 1) * (B + 1);
				return ans;
			}
		}
	}
}

int main()
{
	ifstream fin("B-large-practice.in");
	ofstream fout("B-large-practice.out");

	int cases;
	fin >> cases;
	fin.ignore(1);

	for (int cas = 1; cas <= cases; cas++)
	{
		long long A, B, K;
		fin >> A >> B >> K;
		A--;
		B--;
		K--;
		long long answer = get_answer(A, B, K, ((long long)1) << 31);
		fout << "Case #" << cas << ": "  << answer;

		fout << "\n";
	}
	return 0;
}