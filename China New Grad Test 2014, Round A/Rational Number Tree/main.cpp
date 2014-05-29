#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>
#include <vector>

using namespace std;

typedef unsigned long long ll;

int main()
{
	ifstream fin("B-large.in");
    ofstream fout("B-large.out");

    int cases;
    fin >> cases;
	fin.ignore(1);

    for (int cas = 1; cas <= cases; cas++)
    {
		int id;
		fin >> id;
		if(id==1)
		{
			ll n;
			fin >> n;
			ll p = 1;
			ll q = 1;

			vector<int> s;
			ll m = n;
			while( m > 0)
			{
				if(m%2 == 0)
					s.push_back(0);
				else
					s.push_back(1);
				m/=2;
			}
			reverse(s.begin(),s.end());
			for(ll i = 1;i < s.size(); ++i)
			{
				if( s[i] == 0)
					q = p + q;
				else
					p = p + q;
			}

			 fout << "Case #" << cas << ": "  << p << " " << q << "\n";
		}
		else if(id==2)
		{
			ll p ;
			ll q ;
			fin >> p >> q;

			ll n = 0;
			ll level=1;
			while(p != q)
			{
				if(p>q)
				{
					p = p - q;
					n+=level;
				}
				else
					q = q -p;

				level*=2;
			}
			n+=level;

			fout << "Case #" << cas << ": "  << n << "\n";
			
		}
    }
    return 0;
}
