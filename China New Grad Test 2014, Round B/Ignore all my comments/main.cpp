#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>
#include <vector>
#include <iomanip>

using namespace std;

int main()
{
	ifstream fin("E-small-practice.in");
    ofstream fout("E-small-practice.out", ios_base::out | ios_base::binary);

		string stemp;
		string s;
		while(true)
		{
			getline(fin, stemp, '\n');
			if(fin.fail())
				break;
			s.append(stemp);
			s.append("\n");
		}

		for(int i = 0; i < s.size() - 1; ++i)
		{
			if(s[i] == '*' && s[i + 1] == '/')
			{
				for( int k = i - 1; k > 0; --k)
				{
					if(s[k] == '*' && s[k - 1] == '/')
					{
						s.erase(s.begin() + k - 1, s.begin() + i + 2);
						s.insert(s.begin() + k - 1, (char)1);
						i = k - 1;
						break;
					}
				}
			}
		}

		for(int i = 0; i < s.size(); ++i)
		{
			if(s[i] == 1)
			{
				s.erase(s.begin() + i);
				--i;
			}
		}

        fout << "Case #" << 1 << ":"  ;

		fout << "\n";

		fout << s;

    return 0;
}