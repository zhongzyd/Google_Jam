#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>
#include <vector>
#include <iomanip>

using namespace std;

struct circle
{
	double x;
	double y;
	double r;

	circle()
	{}
	circle(double _x, double _y, double _r): x(_x),y(_y),r(_r)
	{}
};

vector<circle> plants;
int N;
const double eps = 1e-12;

template<typename type> type square(type num)
{
	return num*num;
}

circle get_sprinkler(circle i, circle k, double r, bool p)
{
	r -= i.r;

	double a = i.x - k.x;
	double b = i.y - k.y;

	bool flag = false;
	if(b == 0)
	{
		flag = true;
		swap(a, b);
	}

	double c = (2 * r * (i.r - k.r) + square(i.r - k.r) - square(a) - square(b))/2;

	double delta = 4 * square(a) * square(c) - 4 * (square(a) + square(b)) * (square(c) - square(b) * square(r));

	if(delta < 0)
			return circle(0,0,0);

	double x;
	if(p)
		x = (2 * a * c + sqrt(delta))/(2 * (square(a) + square(b)));
	else
		x = (2 * a * c - sqrt(delta))/(2 * (square(a) + square(b)));
	double y = (c - a * x) / b;

	if(flag)
		swap(x, y);

	x += i.x;
	y += i.y;
	r += i.r;
	double temp1 = square(r - i.r) - (square(x - i.x) + square(y - i.y)); 
	double temp2 = square(r - k.r) - (square(x - k.x) + square(y - k.y)); 
//	if(abs(temp1)>1e-6 || abs(temp2)>1e-6)
//		cout <<"!!"<<"\n";
	return circle(x, y, r);
}

long long cover(circle sprinkler)
{
	long long cov = 0;
	for(int i = 0; i < N; ++i)
	{
		if(sprinkler.r + eps > sqrt(square(sprinkler.x - plants[i].x) + square(sprinkler.y - plants[i].y)) + plants[i].r )
			cov += 1LL << i;
	}
	return cov;
}

bool test(double r)
{
	long long test[40][40];
	for(int i = 0; i < N; ++i)
	for(int k = 0; k < N; ++k)
	{
		circle sprinkler;
		test[i][k] = 0;
		if(i == k)
		{
			if(r >= plants[i].r)
				test[i][k] = 1LL << i;
		}
		else
		{
			sprinkler = get_sprinkler(plants[i], plants[k], r, i > k);
			test[i][k] = cover(sprinkler);
		}
	}

	for(int i = 0; i < N; ++i)
	for(int i1 = 0; i1 < N; ++i1)
	{
		for(int k = 0; k < N; ++k)
		for(int k1 = 0; k1 < N; ++k1)
		{
//			cout << test[i][i1] <<"\n";
//			cout << test[k][k1]<<"\n";
			if((test[i][i1] | test[k][k1]) == (1LL << N) - 1)
				return true;
		}
	}
	return false;
}



int main()
{
//	circle q = get_sprinkler(circle(100,40,2),circle(100,60,2),20);
//	circle w = get_sprinkler(circle(100,60,2),circle(100,40,2),20);
	ifstream fin("D-large-practice.in");
    ofstream fout("D-large-practice.out");

    int cases;
    fin >> cases;
	fin.ignore(1);

    for (int cas = 1; cas <= cases; cas++)
    {
		fin >> N;
		
		plants.resize(N);
		for(int i = 0; i < N; ++i)
		{   
			fin >> plants[i].x;
			fin >> plants[i].y;
			fin >> plants[i].r;
		}

		double low = eps;
		double high = 3000;
		double r = (high + low) / 2;

//		if(cas == 4)
//			cout << cas;

		while(high - low > eps)
		{
			r = (high + low) / 2;
//			cout << r<< "\n";
			if(test(r))
				high = r;
			else
				low = r;
		}

        fout << fixed << setprecision(7) << "Case #" << cas << ": " << r << "\n";
    }
    return 0;
}
