#include<iostream>
#include<algorithm>
using namespace std;

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);

	int number;
	cin >> number;
	int sum{ 0 };
	for (int base = 2; base < number; ++base)
	{
		int num = number;
		while (num > 0)
		{
			sum += num % base;
			num /= base;
		}
	}
	int numerator = sum, denominator = number - 2;
	for (int i = 2; i <= min(numerator, denominator) / 2; ++i)
	{
		if (numerator%i == 0 && denominator%i == 0)
		{
			numerator /= i;
			denominator /= i;
			i = 1;
		}
	}
	cout << numerator << '/' << denominator << endl;
	return 0;
}


