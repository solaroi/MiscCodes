#include <iostream>
#include <cmath>
using namespace std;

//const long long min = -5000000000000000000, max = 5000000000000000000;

long long solve(long long a, long long b, long long &x, long long &y)
{
	if (b == 0)
	{
		x = 1; y = 0; 
		return a;
	}
	long long x1, y1;
	long long a1 = b, b1 = a%b;
	long long gcd = solve(a1, b1, x1, y1);
	x = y1;
	y = x1 - y1*(a / b);
	return gcd;
}

int main()
{
	long long a, b, c;
	long long x, y;
	cin >> a >> b >> c;
	if (a == 0)
	{
		if (c%b == 0)
			cout << 0 << ' ' << -c / b << endl;
		else cout << -1 << endl;
		return 0;
	}
	else if (b == 0)
	{
		if (c%a == 0)
			cout << -c / a << ' ' << 0 << endl;
		else cout << -1 << endl;
		return 0;
	}
	bool reverse = false;
	if (abs(b) > abs(a))
	{
		long long temp = b;
		b = a;
		a = temp;
		reverse = true;
	}
	if (a < 0)
	{
		a *= -1; b *= -1; c *= -1;
	}
	long long gcd = solve(a, abs(b), x, y);
	if (c%gcd == 0)
	{
		if(reverse)
			cout << -b / abs(b)*y*c / gcd << ' ' << -x*c / gcd << endl;
		else cout << -x*c / gcd << ' ' << -b / abs(b)*y*c / gcd << endl;
	}
	else cout << -1 << endl;

	return 0;
}
