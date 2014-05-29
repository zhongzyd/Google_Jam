#include <stdio.h>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;
int main()
{
    ifstream fin("C-large-practice.in");
    ofstream fout("C-large-practice.out");

	const int layoutNum = 8;
	int layout[layoutNum] = {3,3,3,3,3,4,3,4};

	int N;

    fin >> N;
	fin.ignore(1);

    for(int i=1;i<=N;++i)
    {
		string message;
		string keypresses;

		getline(fin,message);

		for(int i=0;i<message.size();i++)
		{
			if(message[i] == ' ')
			{
				if(keypresses.size()>0)
					if(keypresses[keypresses.size()-1] == '0')
							keypresses.push_back(' ');
				keypresses.push_back('0');
			}
			else
			{
				char c = message[i] - 'a' + 1;

				for(int j=0; j<layoutNum; j++)
				{
					if( c > layout[j] )
						c -= layout[j];
					else
					{
						if(keypresses.size()>0)
						if(keypresses[keypresses.size()-1] == '2' + j)
							keypresses.push_back(' ');

						while(true)
						{
							if(c>0)
							{
								keypresses.push_back('2' + j);
								--c;
							}
							else
								break;
						}
					}
				}
				
			}
		}
		fout << "Case #" << i << ": " << keypresses <<"\n";
    }
}
