#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>
#include <vector>
#include <iomanip>

using namespace std;

class Area
{
public:
	long long x1_;
	long long y1_;
	long long x2_;
	long long y2_;
	long long HouseNum_;
	long long sum_distance_to_corner_;

	Area()
	{
	}

	Area(long long x1, long long y1, long long x2, long long y2): x1_(x1), y1_(y1), x2_(x2), y2_(y2)
	{
		initial();
	}

	void initial()
	{
		SetHouseNum();
		SetSumDistanceToCorner();
	}

	void SetHouseNum()
	{
		HouseNum_ = (x2_ - x1_ + 1) * (y2_ - y1_ + 1);
	}

	void SetSumDistanceToCorner()
	{
		sum_distance_to_corner_ = (x2_ - x1_ + y2_ - y1_) * HouseNum_ / 2;
	}
};

Area areas[1000];
int B;


long long SumDistanceFromArea(long long x, long long y, Area &area)
{
	if(x > area.x1_ && x < area.x2_)
	{
		Area area1(area.x1_, area.y1_, x, area.y2_);
		Area area2(x + 1, area.y1_, area.x2_, area.y2_);
		return SumDistanceFromArea(x, y, area1) + SumDistanceFromArea(x, y, area2);
	}
	else if(y > area.y1_ && y < area.y2_)
	{
		Area area1(area.x1_, area.y1_, area.x2_, y);
		Area area2(area.x1_, y + 1, area.x2_, area.y2_);
		return SumDistanceFromArea(x, y, area1) + SumDistanceFromArea(x, y, area2);
	}
	else
	{
		long long dx;
		long long dy;
		if(x <= area.x1_)
			dx = area.x1_ - x;
		else if(x >= area.x2_)
			dx = x - area.x2_;

		if(y <= area.y1_)
			dy = area.y1_ - y;
		else if(y >= area.y2_)
			dy = y - area.y2_;

		return (dx + dy) * area.HouseNum_ + area.sum_distance_to_corner_;
	}
}

long long SumDistanceFromAreas(long long x, long long y)
{
	long long SumDistance = 0;
	for(int i = 0; i < B; ++i)
	{
		SumDistance += SumDistanceFromArea(x, y, areas[i]);
	}
	return SumDistance;
}

int main()
{
	ifstream fin("B-large-practice.in");
    ofstream fout("B-large-practice.out");

    int cases;
    fin >> cases;
	fin.ignore(1);

    for (int cas = 1; cas <= cases; cas++)
    {
		
		fin >> B;

		for(int i = 0; i < B; ++i)
		{
			fin >> areas[i].x1_;
			fin >> areas[i].y1_;
			fin >> areas[i].x2_;
			fin >> areas[i].y2_;
			areas[i].initial();
		}

		long long ans_x;
		long long ans_y;
		long long ans_sum_distance = (1LL << 63) - 1;

		for(int i = 0; i < B; ++i)
		{
			for(int x = areas[i].x1_; x <= areas[i].x2_; ++x)
			for(int y = areas[i].y1_; y <= areas[i].y2_; ++y)
			{
				long long sum_distance = SumDistanceFromAreas(x, y);
				if(ans_sum_distance > sum_distance)
				{
					ans_x = x;
					ans_y = y;
					ans_sum_distance = sum_distance;
				}
				else if(ans_sum_distance == sum_distance)
				{
					if(x < ans_x || (x == ans_x && y < ans_y))
					{
						ans_x = x;
						ans_y = y;
						ans_sum_distance = sum_distance;
					}
				}
			}
		}

        fout << "Case #" << cas << ": "  ;
		fout << ans_x << " " << ans_y << " " << ans_sum_distance;
		fout << "\n";
    }
    return 0;
}