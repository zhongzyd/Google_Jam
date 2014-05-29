#include <stdio.h>
#include <fstream>
#include <iostream>
#include <math.h>
#include <iomanip>


using namespace std;
int main()
{
    ifstream fin("B-small-attempt1.in");
    ofstream fout("B-small-attempt1.out");

	int T;

    fin >> T;

	const double G = 9.8;
    for(int i=1;i<=T;++i)
    {
		double V;
		double D;

		fin >> V;
		fin >> D;
		if(i==30)
		{
			int u;
			u=0;
		}

		double temp = G*D/V/V;
		
		if(temp>1)
			temp=1;
		if(temp<-1)
			temp=-1;

		double angle = asin(temp) / 2 / acos(-1.0) * 180;
		
		fout << "Case #" << i << ": " << setprecision(9) << angle <<"\n";
    }

}
