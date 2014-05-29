#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>
#include <vector>
#include <iomanip>

using namespace std;
const double eps = 0.001;

struct Segment
{
	long long ns;
	long long ne;
	long long ts;
	long long te;
};

long long X, N;
vector<Segment> segments;

long long get_b(Segment &s)
{
	return s.ns - s.ts;
}

bool is_in(long long t, long long n, Segment& s)
{
	if (s.ns <= n && n <= s.ne && s.ts <= t && t <= s.te)
	{
		if (n - s.ns == t - s.ts)
			return true;
	}
	return false;
}

long long left_or_right(long long t, long long n, Segment& s)
{
	long long b = n - t;
	if (b > get_b(s))
		return 0;
	else
		return 1;
}

long long find_front_t(long long t, long long n, Segment& s)
{
	long long bs = s.ns + s.ts;
	long long be = s.ne + s.te;
	long long b = t + n;
	
	if (bs <= b && b <= be)
	{
		if (left_or_right(t, n, s) == 1)
		{
			b += N;
		}
	}

	if (b < bs)
	{
		b += (bs - b) / N * N;
		if (b < bs)
			b += N;
	}
	if (b <= be)
	{
		long long return_t = static_cast<long long>((static_cast<double>(b) - get_b(s)) / 2 - 0.5 + eps);
		if (return_t >= t) 
			return return_t;
	}

	return X;
}

long long find_back_t(long long t, long long n, Segment &s)
{
	long long bs = s.ns + s.ts;
	long long be = s.ne + s.te;
	long long b = n + t;
	
	if (bs <= b && b <= be)
	{
		if (left_or_right(t, n, s) == 0)
		{
			b -= N;
		}
	}

	if (b > be)
	{
		b -= (b - be) / N * N;
		if (b > be)
			b -= N;
	}
	if (b >= bs)
	{
		long long return_t = static_cast<long long>((static_cast<double>(b) - get_b(s)) / 2 + 1 + eps);
		if (return_t <= t)
			return return_t;
	}

	return 0;
}

void refresh_max_t(long long t, long long n, long long& max_t)
{
	if (n == N)
		n = 0;
	else if (n == -1)
		n = N - 1;
	if (t == X + 1 || t == -1)
		return;

	long long front_t = X;
	long long back_t = 0;
	for (long long i = 0; i < segments.size(); ++i)
	{
		if (is_in(t, n, segments[i]))
			return;
			
		long long this_front_t = find_front_t(t, n, segments[i]);
		long long this_back_t = find_back_t(t, n, segments[i]);
		if (front_t > this_front_t)
			front_t = this_front_t;
		if (back_t < this_back_t)
			back_t = this_back_t;
	}
	if (max_t < front_t - back_t)
		max_t = front_t - back_t;
}

void refresh_around(long long t_, long long n_, long long& max_t)
{
	if (n_ == N)
		return;
	else if (n_ == -1)
		return;

	long long t, n;

	t = t_;
	n = n_ + 1;
	refresh_max_t(t, n, max_t);

	t = t_ + 1;
	n = n_ + 1;
	refresh_max_t(t, n, max_t);

	t = t_ + 1;
	n = n_;
	refresh_max_t(t, n, max_t);

	t = t_ + 1;
	n = n_ - 1;
	refresh_max_t(t, n, max_t);

	t = t_;
	n = n_ - 1;
	refresh_max_t(t, n, max_t);

	t = t_ - 1;
	n = n_ - 1;
	refresh_max_t(t, n, max_t);

	t = t_  - 1;
	n = n_;
	refresh_max_t(t, n, max_t);

	t = t_ - 1;
	n = n_ + 1;
	refresh_max_t(t, n, max_t);
}


int main()
{
	ifstream fin("A-large-practice.in");
	ofstream fout("A-large-practice.out");

	long long cases;
	fin >> cases;
	fin.ignore(1);

	for (long long cas = 1; cas <= cases; cas++)
	{
		long long C;
		fin >> C >> X >> N;

		segments.clear();
		long long s, e, t;
		Segment segment;
		for (long long i = 0; i < C; ++i)
		{
			fin >> s;
			s -= 1;
			fin >> e;
			e -= 1;
			fin >> t;

			if (e > s)
			{
				segment.ns = s;
				segment.ts = t;
				segment.ne = e;
				segment.te = t + e - s;
				segments.push_back(segment);
			}
			else
			{
				segment.ns = s;
				segment.ts = t;
				segment.ne = N;
				segment.te = t + N - s;
				segments.push_back(segment);

				segment.ns = -1;
				segment.ts = t + (N - 1) - s;
				segment.ne = e;
				segment.te = t + e + N - s;
				segments.push_back(segment);
			}
			
		}
		
		long long max_t = 0;
		if (segments.size() == 0)
			max_t = X;
		else
		for (long long i = 0; i < segments.size(); ++i)
		{
			refresh_around(segments[i].ts, segments[i].ns, max_t);
			refresh_around(segments[i].te, segments[i].ne, max_t);
		}

		fout << "Case #" << cas << ": ";
		fout << max_t;
		fout << "\n";
	}
	return 0;
}