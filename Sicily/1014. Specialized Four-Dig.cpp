#include <vector>
#include <map>
#include <set>
#include <string>
#include <array>
#include <algorithm>
#include <iostream>
#include <sstream>

using namespace std;
string d2n(int x, int n)
{
	string rslt="";
	int q = x, c;
	while (q >= n)
	{
		c = q%n;
		q = q / n;
		if (c >= 0 && c <= 9)
			rslt = char(c+'0') + rslt;
		else rslt = char(c - 10 + 'A') + rslt;
	}
	if (q >= 0 && q <= 9)
		rslt = char(q + '0') + rslt;
	else rslt = char(q - 10 + 'A') + rslt;
	return rslt;
}

int sum_digits(string str)
{
	int sum = 0;
	for (auto itr = str.begin(); itr != str.end(); ++itr)
	{
		char c = *itr;
		if (c >= '0'&&c <= '9')
			sum = sum + c - '0';
		else sum = sum + c - 'A' + 10;
	}
	return sum;
}

int main()
{
	for (auto i = 1000;i<10000;++i)
	{
		int sum10 = sum_digits(d2n(i, 10));
		int sum12 = sum_digits(d2n(i, 12));
		int sum16 = sum_digits(d2n(i, 16));
		if (sum10 == sum12 && sum10 == sum16)
			cout << i << endl;
	}
	return 0;
}

