#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>
#include <vector>

using namespace std;

int main()
{
	ifstream fin("C-large.in");
    ofstream fout("C-large.out");

    int cases;
    fin >> cases;
	fin.ignore(1);

    for (int cas = 1; cas <= cases; cas++)
    {
		int N;
		fin >> N;

		vector<int> books;
		books.resize(N);
		for(int i=0;i<N;++i)
		{
			fin >> books[i];
		}

		vector<int> Alex;
		vector<int> Bob;
		for(int i=0;i<N;++i)
		{
			if( books[i] % 2 ==0)
				Bob.push_back(books[i]);
			else
				Alex.push_back(books[i]);
		}

		sort(Alex.begin(),Alex.end());
		
		sort(Bob.begin(),Bob.end());

		reverse(Bob.begin(),Bob.end());

		int a=0;
		int b=0;
		for(int i=0;i<N;++i)
		{
			if( books[i] % 2 ==0)
				books[i] = Bob[b++];
			else
				books[i] = Alex[a++];
		}

        fout << "Case #" << cas << ": "  ;
		for(int i=0;i<N;++i)
		{
			fout << books[i] << " ";
		}
		fout <<"\n";
    }
    return 0;
}
