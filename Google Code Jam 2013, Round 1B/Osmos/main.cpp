#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>
#include <vector>
#include <iomanip>

using namespace std;

int main()
{
	ifstream fin("A-large-practice.in");
    ofstream fout("A-large-practice.out");

    int cases;
    fin >> cases;
	fin.ignore(1);

    for (int cas = 1; cas <= cases; cas++)
    {
		int A;
		int N;
		fin >> A >> N;
		
		vector<int> motes;
		motes.resize(N);
		for(int i = 0; i < N; ++i)
			fin >> motes[i];

		sort(motes.rbegin(), motes.rend());

		int count_best = N + 1;
		int count = 0;

		while(motes.size() > 0 && count <= N)
		{
			if(A > motes.back())
			{
				A += motes.back();
				motes.pop_back();
			}
			else if(A + A - 1 > motes.back())
			{
				motes.push_back(A - 1);
				++count;
			}
			else
			{
				if(count_best > count + motes.size())
					count_best = count + motes.size();

				motes.push_back(A - 1);
				++count;
			}
		}

		if(count_best > count)
			count_best = count;

        fout << "Case #" << cas << ": "  ;
		fout << count_best;
		fout << "\n";
    }
    return 0;
}