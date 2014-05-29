#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>
#include <vector>
#include <iomanip>

using namespace std;

int main()
{
	ifstream fin("B-large.in");
	ofstream fout("B-large.out");
	fout.setf(ios::fixed, ios::floatfield);
	fout.precision(7);
	int cases;
	fin >> cases;
	fin.ignore(1);

	for (int cas = 1; cas <= cases; cas++)
	{
		double C, F, X;
		fin >> C >> F >> X;
		double time = 0;
		double speed = 2;
		double time1;
		double time2;
		while (true)
		{
			time1 = time + X / speed;
			time2 = time + C / speed + X / (speed + F);

			if (time2 < time1)
			{
				time += C / speed;
				speed += F;
			}
			else
			{
				time = time1;
				break;
			}

		}


		fout << "Case #" << cas << ": " << time;

		fout << "\n";
	}
	return 0;
}