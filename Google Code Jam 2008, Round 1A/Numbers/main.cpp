#include <stdio.h>
#include <fstream>
#include <iostream>
#include <list>
#include <string>
#include <math.h>

using namespace std;
int main()
{
	 ifstream fin("C-small-practice.in");
    ofstream fout("C-small-practice.out");

	char a;
	int b=10;
	fin >> noskipws >> a >>b;
	cout <<a;
	cout<<b;
	cin>>a;
	int T;

    fin >> T;


    for(int i=1;i<=T;++i)
    {
		int n;
		fin >>n;

		long double k=3+sqrt(5);
		long double answer=1;
		for(int j=0;j<n;j++)
		{
			answer *= k;
		}

		if(answer>=1000)
			answer = answer-((long long)(answer/1000.0))*1000;

		if(answer<10)
			fout << "Case #" << i << ": " << "00" << answer <<"\n";
		else if(answer<100)
			fout << "Case #" << i << ": " << "0" << answer <<"\n";
		else
			fout << "Case #" << i << ": " << answer <<"\n";
    }

}
