#include <stdio.h>
#include <fstream>
#include <iostream>
#include <list>
#include <string>

using namespace std;
int main()
{
    ifstream fin("C-small-2-attempt0.in");
    ofstream fout("C-small-2-attempt0.out");

	int T;

    fin >> T;

    for(int i=1;i<=T;++i)
    {
		int N;
		fin >> N;
		fin.ignore(1);

		list<string> cards;
		string temp;
		for(int j=0;j<N;j++)
		{
			getline(fin,temp);
			cards.push_back(temp);
		}

		int count = 0;
		for(list<string>::iterator ite=cards.begin() ; ite!=cards.end() ; )
		{
			int insertOrNot=0;
			for(list<string>::iterator ite1=cards.begin() ; ite1!=ite ; ++ite1)
			{
				if(*ite < *ite1)
				{
					insertOrNot=1;
					++count;
					cards.insert(ite1,*ite);
					break;
				}
			}

			if(insertOrNot==1)
			{
				cards.erase(ite++);
			}
			else
				++ite;
		}

		fout << "Case #" << i << ": " << count <<"\n";
    }

}
