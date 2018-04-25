#include<iostream>
using namespace std;

typedef long long ll;

struct Point
{
	ll x_{ 0 }, y_{ 0 };
	Point(ll x = 0, ll y = 0) :x_(x), y_(y) {};
	Point(const Point &p) :x_(p.x_), y_(p.y_) {};
	void operator = (const Point &p) { x_ = p.x_; y_ = p.y_; };
	bool operator == (const Point &p) const { return x_ == p.x_&&y_ == p.y_; };
	Point operator - (const Point &p) const { return Point(x_ - p.x_, y_ - p.y_); };
	ll operator *(const Point &p) const { return x_*p.x_ + y_*p.y_; };
	ll cross(const Point &p) const { return x_*p.y_ - y_*p.x_; };
};

struct DirectedSegment
{
	Point startp_, endp_;
	DirectedSegment() = default;
	DirectedSegment(const Point &startp, const Point &endp) :startp_(startp), endp_(endp){};
	bool GoodAngleWith(const DirectedSegment &dseg);
	bool WellDividedBy(const Point &p);
};

bool DirectedSegment::GoodAngleWith(const DirectedSegment &dseg) 
{
	Point p1 = endp_ - startp_, p2 = dseg.endp_ - startp_;
	return p1.cross(p2) != 0 && p1*p2 >= 0;
}

bool DirectedSegment::WellDividedBy(const Point &p) {
	Point p1 = p - startp_, p2 = endp_ - startp_;
	ll dist1 = p1*p2, dist2 = p2*p2;
	return p1.cross(p2) == 0 && 5 * dist1 >= dist2 && 5 * dist1 <= 4 * dist2;
};

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);

	int num_cases;
	cin >> num_cases;
	Point p[6];
	for (int i = 0; i < num_cases; ++i)
	{
		for (int j = 0; j < 6; ++j)
			cin >> p[j].x_ >> p[j].y_;
		int start1{ -1 }, start2{ -1 };//start1 start2 are the index of the common point or the peak of "A"
		bool find_common_point = false;
		for (int j = 0; j < 5; ++j)
		{
			for (int k = j & 1 ? j + 1 : j + 2; k < 6; ++k)
			{
				if (p[j] == p[k])
				{
					start1 = j;
					start2 = k;
					find_common_point = true;
					break;
				}
			}
			if (find_common_point)
				break;
		}
		if (!find_common_point)
		{
			cout << "NO" << endl;
			continue;
		}
		int end1 = start1 & 1 ? start1 - 1 : start1 + 1;
		int end2 = start2 & 1 ? start2 - 1 : start2 + 1;
		DirectedSegment dseg1(p[start1], p[end1]), dseg2(p[start2], p[end2]);
		if (!dseg1.GoodAngleWith(dseg2))
		{
			cout << "NO" << endl;
			continue;
		}
		int h = (15 - start1 - end1 - start2 - end2) >> 1;
		if ((dseg1.WellDividedBy(p[h]) && dseg2.WellDividedBy(p[h + 1])) || \
			(dseg1.WellDividedBy(p[h + 1]) && dseg2.WellDividedBy(p[h])))
			cout << "YES" << endl;
		else cout << "NO" << endl;
	}
	return 0;
}
