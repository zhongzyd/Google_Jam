#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>
#include <vector>

using namespace std;

string ans;

void plusNum(int num)
{
	if(num == 0)
		ans+="zero ";
	else if(num == 1)
		ans+="one ";
	else if(num == 2)
		ans+="two ";
	else if(num == 3)
		ans+="three ";
	else if(num == 4)
		ans+="four ";
	else if(num == 5)
		ans+="five ";
	else if(num == 6)
		ans+="six ";
	else if(num == 7)
		ans+="seven ";
	else if(num == 8)
		ans+="eight ";
	else if(num == 9)
		ans+="nine ";
}

int main()
{
	ifstream fin("A-large.in");
    ofstream fout("A-large.out");

    int cases;
    fin >> cases;
	fin.ignore(1);

    for (int cas = 1; cas <= cases; cas++)
    {
		ans.clear();

		string N;
		fin >> N;

		vector<int> f;
		int temp=0;
		int count=0;
		char henxian;
		while(count < N.size())
		{
			fin >> temp;
			count += temp;
			f.push_back(temp);
			if(count < N.size())
				fin >> henxian; 
		}

		vector<int> c;

		int pos=0;
		for(int i=0;i<f.size();++i)
		{
			int k = f[i];
			c.clear();
			for(int j=0;j<k;++j)
			{
				c.push_back(N[pos++] - '0');
			}

			vector<int> a;
			/*
			if(cas == 11)
			{
				int lll;
				lll=0;
			}*/
			for(int u=0;u<c.size();)
			{
				a.clear();
				a.push_back(c[u++]);
				while( (u<c.size()) && (c[u]==c[u-1]) )
				{
					a.push_back(c[u++]);
				}
				int asize=a.size();
				if(asize == 2)
					ans+="double ";
				else if(asize == 3)
					ans+="triple ";
				else if(asize == 4)
					ans+="quadruple ";
				else if(asize == 5)
					ans+="quintuple ";
				else if(asize == 6)
					ans+="sextuple ";
				else if(asize == 7)
					ans+="septuple ";
				else if(asize == 8)
					ans+="octuple ";
				else if(asize == 9)
					ans+="nonuple ";
				else if(asize == 10)
					ans+="decuple ";
				else if(asize > 10)
				{
					for(int p=0;p<asize-1;++p)
					{
						plusNum(a[0]);
					}
				}

				plusNum(a[0]);
			}
		}


        fout << "Case #" << cas << ": "  << ans << "\n";
    }
    return 0;
}
