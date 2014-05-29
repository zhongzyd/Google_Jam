#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>
#include <vector>
#include <iomanip>

using namespace std;

int main()
{
	ifstream fin("test.in");
    ofstream fout("test.out");

    int cases;
    fin >> cases;
	fin.ignore(1);

    for (int cas = 1; cas <= cases; cas++)
    {

        fout << "Case #" << cas << ": "  ;

		fout << "\n";
    }
    return 0;
}