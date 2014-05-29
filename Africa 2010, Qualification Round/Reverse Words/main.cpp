#include <stdio.h>
#include <fstream>
#include <iostream>
#include <string>

using namespace std;
int main()
{
    ifstream fin("B-large-practice.in");
    ofstream fout("B-large-practice.out");
    int N;
    string sinput;
    string soutput;
    size_t b;
    size_t e;

    fin >> N;
	fin.ignore(1);

    for(int i=1;i<=N;++i)
    {
        getline(fin,sinput);

        reverse(sinput.begin(),sinput.end());

        for(b=0;b < sinput.size();b=e+1)
        {
                e = sinput.find_first_of(' ',b);
                if(e!=string::npos)
                      reverse(sinput.begin()+b,sinput.begin()+e);
                else
				{
                      reverse(sinput.begin()+b,sinput.end());
					  break;
				}
		}
        fout << "Case #" << i << ": " << sinput <<"\n";
    }
}
