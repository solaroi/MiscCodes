#include<iostream>
using namespace std;


int main()
{
	int y, w, d;
	cin >> y >> w;
	d = y >= w ? y : w;
	int numer = 6 - d + 1;
	int demer = 6;
	for (int i = 2; i <= 3; ++i)
	{
		if (numer%i == 0)
		{
			numer /= i;
			demer /= i;
		}
	}
	cout << numer << '/' << demer << endl;
	return 0;
}