
#include <iostream>
#include <iomanip>
#include <cmath>
#include <limits>
using namespace std;
double crd[3][3];
double variation_sum(double x, double y)
{
	double d_r_ratio[3];
	for (auto i = 0; i < 3; ++i)
		d_r_ratio[i] = sqrt((x - crd[i][0])*(x - crd[i][0]) + (y - crd[i][1])*(y - crd[i][1])) / crd[i][2];
	double var_sum{ 0 };
	for(auto i=0;i<3;++i)
		var_sum = var_sum + pow((d_r_ratio[(i + 1) % 3] - d_r_ratio[i]), 2);
	return var_sum;
}
int main()
{

	double x0{ 0 }, y0{ 0 };
	for (auto i = 0; i < 3; ++i)
	{
		cin >> crd[i][0] >> crd[i][1] >> crd[i][2];
		x0 = x0 + crd[i][0]; y0 = y0 + crd[i][1];
	}
	x0 = x0 / 3; y0 = y0 / 3;
	double err = 0.000001, sum_diff{ variation_sum(x0,y0) }, step{ 1 };
	const double x_diff[4]{ 1,0,-1,0 };
	const double y_diff[4]{ 0,-1,0,1 };
	do
	{
		double sum_diff_min{ std::numeric_limits<double>::max() };
		double x_prior, y_prior;
		for (auto d = 0; d < 4; ++d)
		{
			double x_moved = x0 + step*x_diff[d];
			double y_moved = y0 + step*y_diff[d];
			double var_sum_moved{ variation_sum(x_moved,y_moved) };
			if (var_sum_moved < sum_diff_min)
			{
				x_prior = x_moved; y_prior = y_moved;
				sum_diff_min = var_sum_moved;
			}
		}
		if (sum_diff_min < sum_diff)
		{
			cout << fixed << setprecision(10) << sum_diff << " " << sum_diff_min << endl;
			cout << fixed << setprecision(10) << x0 << " " << y0 << endl;
			cout << fixed << setprecision(10) << step << endl;
			x0 = x_prior; y0 = y_prior;
			sum_diff = sum_diff_min;
			step = 2 * step;
		}
		else step = 0.5*step;

	} while (sum_diff > err);
	cout << fixed << setprecision(5) << x0 << " " << y0 << endl;
	return 0;
}

