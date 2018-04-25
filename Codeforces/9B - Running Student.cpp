#include<iostream>
#include<cmath>
using namespace std;

double Dis(double x1, int y1, double x2, double y2)
{
	return sqrt((x1 - x2)*(x1 - x2) + (y1 - y2)*(y1 - y2));
}

int main()
{
	int n;
	double vb, vs;
	cin >> n >> vb >> vs;
	double *stop = new double[n + 1];
	for (int i = 1; i <= n; ++i)
		cin >> stop[i];
	double xu, yu;
	cin >> xu >> yu;

	int get_off{ 2 };
	if (vs >= vb)
	{
		if (vs == vb && yu == 0 && xu > stop[2])
		{
			do { ++get_off; } while (stop[get_off] <= xu && get_off <= n);
			--get_off;
		}
		
	}
	else
	{
		int cnt = 1;
		double min_time = 2000000000, min_su;
		while (stop[cnt] < xu && cnt < n)
		{
			++cnt;
			double stu_univ = Dis(stop[cnt], 0, xu, yu);
			double time = stop[cnt] / vb + stu_univ / vs;
			if (time < min_time)
			{
				get_off = cnt;
				min_time = time;
				min_su = stu_univ;
			}
			else if (time == min_time && stu_univ < min_su)
			{
				get_off = cnt;
				min_su = stu_univ;
			}
		}
	}
	cout << get_off << endl;
	return 0;
}