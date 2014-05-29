#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>
#include <vector>
#include <iomanip>

using namespace std;

int N;
double eps = 1e-13;

struct Point
{
	double x;
	double y;
};

bool CompareX(Point p1, Point p2)
{
	return p1.x < p2.x;
}

bool CompareY(Point p1, Point p2)
{
	return p1.y < p2.y;
}

void rotate(Point &p, double angle)
{
	Point p_after_rotation;
	p_after_rotation.x = p.x * cos(angle) - p.y * sin(angle);
	p_after_rotation.y = p.x * sin(angle) + p.y * cos(angle);
	p = p_after_rotation;
}

Point FindCenter(vector<Point> ps)
{
		long double xa = 0, ya = 0;

		sort(ps.begin(), ps.end(), CompareX);
		xa = (ps[2 * N].x + ps[2 * N - 1].x) / 2;
		
		sort(ps.begin(), ps.end(), CompareY);
		ya = (ps[2 * N].y + ps[2 * N - 1].y) / 2;

		Point center;
		center.x = xa;
		center.y = ya;

		return center;
}

int TestCenter(vector<Point> &ps, Point center)
{
	int count = 0;
	for(int i = 0; i < 4 * N; ++i)
	{
		ps[i].x -= center.x;
		ps[i].y -= center.y;
		if(ps[i].y == 0)
			cout << "!";
		if(ps[i].y > 0)
		{
			if(ps[i].x > 0)
				++count;
			else if(ps[i].x < 0)
				--count;
			else
				cout << "!";
		}
	}
	return count;
}

int Test(vector<Point> ps, double angle)
{
	for(int i = 0; i < 4 * N; ++i)
	{
		rotate(ps[i], angle);
	}
	Point center = FindCenter(ps);
	return TestCenter(ps, center);
}


int main()
{
	ifstream fin("C-large-practice.in");
    ofstream fout("C-large-practice.out");

    int cases;
    fin >> cases;
	fin.ignore(1);

    for (int cas = 1; cas <= cases; cas++)
    {
		fin >> N;

		vector<Point> ps;

		ps.resize(4 * N);

		long double xa = 0, ya = 0;

		for(int i = 0; i < 4 * N; ++i)
		{
			fin >> ps[i].x;
			fin >> ps[i].y;
		}

		double low = eps;
		double high = acos(0.0) + eps;
		double angle;
		int count_low, count_angle, count_high;

		do
		{
			angle = (low + high) / 2;
			count_low = Test(ps, low);
			count_angle = Test(ps, angle);
			count_high = Test(ps, high);

			if(count_angle == 0)
				break;
			
			if(count_low * count_angle <= 0)
				high = angle;
			else
				low = angle;
		}
		while(true);

		for(int i = 0; i < 4 * N; ++i)
		{
			rotate(ps[i], angle);
		}
		Point center = FindCenter(ps);

		Point some_point = center;
		some_point.x += 1e8;

		rotate(center, -angle);
		rotate(some_point, -angle);

        fout << "Case #" << cas << ": "  ;

		fout <<  fixed << setprecision(9) << center.x << " " << center.y << " "  << some_point.x << " " << some_point.y ;

		fout << "\n";
    }
    return 0;
}