#include <stdio.h>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <set>

using namespace std;

typedef struct
{
	string name1;
	string name2;
	int visited;
} namePair;

int main()
{
    ifstream fin("A-small-2-attempt0.in");
    ofstream fout("A-small-2-attempt0.out");

	int T;

    fin >> T;
	fin.ignore(1);

    for(int i=1;i<=T;++i)
    {
		int M;
		fin >> M;
		fin.ignore(1);

		vector<namePair> pairs;
		namePair pair;

		set<string> group1;
		vector<string> group1newInsert;
		set<string> group2;
		vector<string> group2newInsert;

		for(int i=0;i<M;++i)
		{
			fin >> pair.name1;
			fin >> pair.name2;
			pair.visited=0;
			pairs.push_back(pair);
		}

		int YesOrNo=1;
		for(int i=0;i<M;++i)
		{
			if( pairs[i].visited != 0 )
				continue;

			group1newInsert.push_back(pairs[i].name1);
			group2newInsert.push_back(pairs[i].name2);
			pairs[i].visited = 1;

			while((group1newInsert.size()>0 || group2newInsert.size()>0) && YesOrNo != 0)
			{
				if(group1newInsert.size()>0)
				{
					string nameTemp=group1newInsert.back();
					group1newInsert.pop_back();

					if(group2.count(nameTemp)==1)
						YesOrNo=0;
					group1.insert(nameTemp);

					for(int j=i; j<M; ++j)
					{
						if( pairs[j].visited != 0 )
							continue;

						if( pairs[j].name1 == nameTemp )
						{
							group2newInsert.push_back(pairs[j].name2);
							pairs[j].visited = 1;
						}
						else if( pairs[j].name2 == nameTemp )
						{
							group2newInsert.push_back(pairs[j].name1);
							pairs[j].visited = 1;
						}
					}
				}

				if(group2newInsert.size()>0)
				{
					string nameTemp=group2newInsert.back();
					group2newInsert.pop_back();

					if(group1.count(nameTemp)==1)
						YesOrNo=0;
					group2.insert(nameTemp);

					for(int j=i; j<M; ++j)
					{
						if( pairs[j].visited != 0 )
							continue;

						if( pairs[j].name1 == nameTemp )
						{
							group1newInsert.push_back(pairs[j].name2);
							pairs[j].visited = 1;
						}
						else if( pairs[j].name2 == nameTemp )
						{
							group1newInsert.push_back(pairs[j].name1);
							pairs[j].visited = 1;
						}
					}
				}

			}
		}

		if(YesOrNo==1)
			fout << "Case #" << i << ": " << "Yes" <<"\n";
		else
			fout << "Case #" << i << ": " << "No" <<"\n";


    }
}