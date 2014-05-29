#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>
#include <vector>
#include <iomanip>

using namespace std;

int main()
{
	ifstream fin("A-small-attempt2.in");
	ofstream fout("A-small-attempt2.out");

	int cases;
	fin >> cases;
	fin.ignore(1);

	int cards[4];
	int choice;
	int temp;
	vector<int> result;
	for (int cas = 1; cas <= cases; cas++)
	{
		result.clear();
		fin >> choice;
		for (int i = 1; i <= 4; ++i)
		for (int h = 0; h < 4; ++h)
		{
			if (i == choice)
				fin >> cards[h];
			else
				fin >> temp;
		}
		fin >> choice;
		for (int i = 1; i <= 4; ++i)
		for (int h = 0; h < 4; ++h)
		{
			fin >> temp;
			if (i == choice)
			{
				for (int k = 0; k < 4; ++k)
				{
					if (cards[k] == temp)
						result.push_back(temp);
				}
			}
		}

		

		if (result.size() == 0)
			fout << "Case #" << cas << ": " << "Volunteer cheated!";
		else if (result.size() == 1)
			fout << "Case #" << cas << ": " << result.back();
		else
			fout << "Case #" << cas << ": " << "Bad magician!";
		fout << "\n";
	}
	return 0;
}