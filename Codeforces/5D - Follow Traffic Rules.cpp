#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;

typedef long double ld;
ld a, vm, l, d, w;
ld full_speed(ld v0, ld x)
{
	ld x1 = (vm*vm - v0*v0) / 2 / a;
	if (x <= x1)
		return (sqrt(v0*v0 + 2 * a*x) - v0) / a;
	else
		return (vm - v0) / a + (x - x1) / vm;
}

int main()
{
	cin >> a >> vm >> l >> d >> w;
	ld t_min;
	ld w_square = w*w, d_veloc = 2 * a*d;
	if (w_square >= d_veloc || (d_veloc > w_square && w_square >= vm*vm))
		t_min = full_speed(0, l);
	else
	{
		if (2 * vm*vm >= w_square + d_veloc)
			t_min = (sqrt(2 * w_square + 2 * d_veloc) - w) / a + full_speed(w, l - d);
		else
			t_min = (vm - w) / a + d / vm + w_square / (2 * a*vm) + full_speed(w, l - d);
		//t_min = vm / a + (vm - w) / a + (d - (vm*vm - w*w) / 2 / a - vm*vm / 2 / a) / vm + full_speed(w, l - d);
	}
	cout << fixed << setprecision(10) << t_min << endl;
	return 0;
}