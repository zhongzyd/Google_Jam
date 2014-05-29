#include <fstream>
#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <iomanip>

using namespace std;

const double kEps = 1e-13;

inline double square(double num)
{
	return num*num;
}

class Point
{
public:
	int x_;
	int y_;
	int num_;
	Point()
	{}
	Point(int x, int y, int num): x_(x), y_(y), num_(num)
	{}

	bool operator < (const Point & point)
	{
		if(x_ < point.x_ || (x_ == point.x_ && y_ < point.y_))
			return true;
		else
			return false;
	}
};

double GetTheta(Point a, Point b, Point c)
{
	double x1 = b.x_ - a.x_;
	double y1 = b.y_ - a.y_;
	double x2 = c.x_ - b.x_;
	double y2 = c.y_ - b.y_;
	double theta = (x1 * x2 + y1 * y2) / sqrt((x1*x1+y1*y1)*(x2*x2+y2*y2));
	return theta;
}

void GetPosts(vector<Point> &posts, vector<Point> &out_posts, int up_or_down)
{
	out_posts.push_back(Point(posts[0].x_, posts[0].y_ + up_or_down, posts[0].num_));
	out_posts.push_back(posts[0]);

	int i = 1;

	int posts_size = posts.size();
	int out_posts_size = out_posts.size();
	while(true)
	{
		double theta = -2;
		int remember_k = -1;
		for(int k = i; k < posts_size; ++k)
		{
			double this_theta = GetTheta(out_posts[out_posts_size - 2], out_posts[out_posts_size - 1], posts[k]);
			
			if(this_theta > theta + kEps)
			{
				theta = this_theta;
				remember_k = k;
			}
		}

		i = remember_k;

		out_posts.push_back(posts[remember_k]);
		++out_posts_size;
		if(remember_k != posts_size - 1)
		{
			posts.erase(posts.begin() + remember_k);
			--posts_size;
		}
		else
			break;
	} 
	out_posts.erase(out_posts.begin());
}

double GetArea(vector<Point> posts, double base)
{
	double area = 0;
	for(int i = 1; i < posts.size(); ++i)
	{
		double up_base = posts[i].y_ - base;
		double down_base = posts[i - 1].y_ - base;
		double height = posts[i].x_ - posts[i - 1].x_;
		area += (up_base + down_base) * height / 2;
	}
	return area;
}

class aa
{
public:
	int a;
	void p()
	{
		int d;
		cout << &d <<" " << d <<"\n";
	}
};
class bb : public aa
{
public:
	int b;
	void p1()
	{
		cout << this <<"\n";
		cout << &a <<" " << a <<"\n";
		cout << &b <<" " << b << "\n";
	}
};
struct mybitfields
{
short a : 2;
unsigned short b : 5;
unsigned short c : 8;
}test;

int main()
{  
	int ass = (10008)%10007;
	cout << ass;
	int i;
test.a=-2;
test.b=3;
test.c=0;
i=*((short *)&test);
printf("%d ",test.a);
	int a=-1;
	int b=a/2;
	cout << b<<"\n";
	bb *k = (bb *)operator new(sizeof(bb));
	int d1;
	int d2;
	bb *d = (bb*)&d2;
	d->p1();
	int *q = (int *)d;
	*q = 12;
	*(q+1) = 13;
	d->p1();
	cout << "\n";
	cout << &d1 <<"\n";
	cout << &d2 <<"\n";
	int qww;
	cin >>hex>> qww;

	*((int *)qww) = 99;
	d->p1();
//	c->p();
//	cout << &d <<"\n";
	ifstream fin("B-large-practice.in");
    ofstream fout("B-large-practice.out");

    int cases;
    fin >> cases;
	fin.ignore(1);

    for (int cas = 1; cas <= cases; cas++)
    {
		int N;
		fin >> N;

		vector<Point> posts;
		posts.resize(N);
		for(int i = 0; i < N; ++i)
		{
			fin >> posts[i].x_;
			fin >> posts[i].y_;
			posts[i].num_ = i;
		}
		
		sort(posts.begin(), posts.end());

		vector<Point> up_posts;
		vector<Point> up_down_posts = posts;
		GetPosts(up_down_posts, up_posts, -1);

		vector<Point> down_posts;
		vector<Point> down_up_posts = posts;
		GetPosts(down_up_posts, down_posts, 1);

		const double base = -50001;

		double area_up = GetArea(up_posts, base) - GetArea(up_down_posts, base);
		double area_down = GetArea(down_up_posts, base) - GetArea(down_posts, base); 

        fout << "Case #" << cas << ": "  ;

		if(area_up > area_down)
		{
			for(int i = 0; i < up_posts.size(); ++i)
				fout << up_posts[i].num_ << " ";

			for(int i = up_down_posts.size() - 2; i > 0; --i)
				fout << up_down_posts[i].num_ << " ";
		}
		else
		{
			for(int i = 0; i < down_posts.size(); ++i)
				fout << down_posts[i].num_ << " ";

			for(int i = down_up_posts.size() - 2; i > 0; --i)
				fout << down_up_posts[i].num_ << " ";
		}

		fout << "\n";
    }
    return 0;
}
