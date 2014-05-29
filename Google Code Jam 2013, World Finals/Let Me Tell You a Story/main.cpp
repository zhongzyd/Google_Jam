#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>
#include <vector>
#include <iomanip>
#include <BinaryIndexedTree>

using namespace std;

struct Minister
{
	int salary;
	int rank;
	int s_rank;
};

bool CompareRank(Minister m1, Minister m2)
{
	if(m1.rank < m2.rank)
		return true;
	else
		return false;
}

bool CompareSalary(Minister m1, Minister m2)
{
	if(m1.salary < m2.salary)
		return true;
	else if(m1.salary == m2.salary)
		return m1.rank > m2.rank;
	else
		return false;
}

int A(int  N)
{
	int i = 1;
	while(N > 0)
	{
		i *= N;
		i %= 10007;
		--N;
	}
	return i;
}


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
		vector<Minister> ministers;
		ministers.resize(N);

		for (int i = 0; i < N; ++i)
		{
			ministers[i].rank = i + 1;
			fin >> ministers[i].salary;
		}

		sort(ministers.rbegin(), ministers.rend(), CompareSalary);

		for (int i = 0; i < N; ++i)
			ministers[i].s_rank = i + 1;

		sort(ministers.begin(), ministers.end(), CompareRank);
		
		BinaryIndexedTree<int> bit_k(N);
		BinaryIndexedTree<int> bit_temp(N);
		BinaryIndexedTree<int> bit_k1(N);

		for (int i = 1; i <= N; ++i)
		{
			bit_k.Update(i, 1);
		}

		int flag = 0;
		for (int i = 1; i < N; ++i)
		{
			if (ministers[i].salary > ministers[i - 1].salary)
				flag = 1;
		}

		int sum = 0;
		if (flag == 0)
			sum = 1;
		else
		for (int k = 1; k < N; ++k)
		{
			for (int i = 0; i < N; ++i)
			{
				bit_temp.UpdateSingle(ministers[i].s_rank, bit_k.ReadSingle(ministers[i].s_rank));
				bit_k1.UpdateSingle(ministers[i].s_rank, bit_temp.Read(ministers[i].s_rank - 1) % 10007);
			}
			int ak = bit_k.Read(N) % 10007;
			int ak1 = bit_k1.Read(N) % 10007;
			int nk = A(N - k);
			int nk1 = A(N - k - 1);

			sum += nk * ak - ak1 * nk1 % 10007 * (k + 1);
			sum %= 10007;

			bit_temp.Clear();
			swap(bit_k, bit_k1);
		}

		while (sum < 0)
			sum += 10007;
		

        fout << "Case #" << cas << ": " << sum;

		fout << "\n";

    }
    return 0;
}
