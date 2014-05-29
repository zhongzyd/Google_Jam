#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>
#include <vector>
#include <list>
#include <iomanip>

using namespace std;

int main()
{
	ifstream fin("D-large.in");
	ofstream fout("D-large.out");

	int cases;
	fin >> cases;
	fin.ignore(1);

	for (int cas = 1; cas <= cases; cas++)
	{
		list<double> naomi;
		list<double> ken;

		int N;
		fin >> N;

		double temp;
		for (int i = 0; i < N; ++i)
		{
			fin >> temp;
			naomi.push_back(temp);
		}
		for (int i = 0; i < N; ++i)
		{
			fin >> temp;
			ken.push_back(temp);
		}
		naomi.sort();
		ken.sort();

		list<double>::iterator ni = naomi.begin();
		list<double>::iterator ki = ken.begin();

		int Deceitful_War = 0;
		for (int i = 0; i < N; ++i)
		{
			if (*ni > *ki)
			{
				++Deceitful_War;
				++ki;
			}
			++ni;
		}

		int WAR = 0;
		ni = naomi.begin();
		for (int i = 0; i < N; ++i)
		{
			ki = ken.begin();
			while (ki != ken.end())
			{
				if (*ki > *ni)
					break;
				else
					++ki;
			}
			if (ki != ken.end())
			{
				ken.erase(ki);
				++ni;
			}
			else
			{
				WAR = ken.size();
				break;
			}
			
		}
		



		fout << "Case #" << cas << ": " << Deceitful_War << " " << WAR;

		fout << "\n";
	}
	return 0;
}