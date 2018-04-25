#include<iostream>
#include<cmath>
using namespace std;

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	
	double x;
	cin >> x;
	if (x < 0)
		x *= -1;
	double x1 = (sqrt(8*x + 1) - 1) / 2;
	int num_minjumps= int(x1);
	if (x1 != num_minjumps)
	{
		++num_minjumps;
		int xr = num_minjumps*(num_minjumps + 1) / 2;
		if ((xr - int(x)) % 2 != 0)
		{
			++num_minjumps;
			if (num_minjumps % 2 == 0)
				++num_minjumps;
		}
	}
	cout << num_minjumps << endl;
	return 0;
}


