#include<iostream>
#include<cmath>
using namespace std;

struct Point
{
	double x, y;
};

const double eps = 0.0000000001;
double t1, t2;
Point cinema, house, shop;

double Dis(Point &p1, Point &p2)
{
	return sqrt((p1.x - p2.x)*(p1.x - p2.x) + (p1.y - p2.y)*(p1.y - p2.y));
}

double Max_dis(double portion)
{
	Point p;
	p.x = shop.x + (house.x - shop.x)*portion;
	p.y = shop.y + (house.y - shop.y)*portion;
 	double cp = Dis(cinema, p), sp = Dis(shop, p), ph = Dis(p, house);
	if ((cp + sp < t1) && (cp + ph < t2))
		return (t1 - sp) < (t2 - ph) ? (t1 - sp) : (t2 - ph);
	double l = 0.0, r = 1.0, ans{ 0 };
	Point m;
	for (int i = 0; i < 500; ++i)
	{
		double mid = (l + r) / 2.00;
		m.x = cinema.x + (p.x - cinema.x)*mid;
		m.y = cinema.y + (p.y - cinema.y)*mid;
		double cm = Dis(cinema, m), sm = Dis(shop, m), mh = Dis(m, house);
		if ((cm + sm < t1) && (cm + mh < t2))
			l = mid;
		else r = mid;
	}
	m.x = cinema.x + (p.x - cinema.x)*l;
	m.y = cinema.y + (p.y - cinema.y)*l;
	return Dis(cinema, m);
}


int main()
{
	cin >> t1 >> t2;
	cin >> cinema.x >> cinema.y >> house.x >> house.y >> shop.x >> shop.y;
	double cs = Dis(cinema, shop), sh = Dis(shop, house), ch = Dis(cinema, house);
	if (ch + t2 >= cs + sh)
	{
		double max_dis = (ch + t2) < (cs + sh + t1) ? (ch + t2) : (cs + sh + t1);
		cout << fixed << max_dis << endl;
		return 0;
	}
	t1 = t1 + cs + eps;
	t2 = t2 + ch + eps;
	double l = 0.0, r = 1.0, max_dis = 0.0;
	for (int i = 0; i < 500; ++i)
	{
		double mid1 = (r - l) / 3.00 + l, mid2 = (r - l) * 2.00 / 3.00 + l;
		double max1 = Max_dis(mid1), max2 = Max_dis(mid2);
		if (max1 > max2)
			r = mid2;
		else l = mid1;
		double max3 = max1 > max2 ? max1 : max2;
		max_dis = max3 > max_dis ? max3 : max_dis;
	}
	cout << fixed << max_dis << endl;
	return 0;
}