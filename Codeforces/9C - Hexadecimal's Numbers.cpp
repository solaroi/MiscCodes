#include<iostream>
#include<cmath>
using namespace std;

int num_tested[10];
int len;

void AddOne()
{
	int carry{ 1 };
	for (int i = 0; i <= len; ++i)
	{
		if (num_tested[i] == 0)
		{
			num_tested[i] += carry;
			break;
		}
		else
		{
			num_tested[i] = 0;
			carry = 1;
		}
	}
	++len;
}

int Cal()
{
	int val{ 0 }, base{ 1 };
	for (int i = 0; i < len; ++i)
	{
		val += (num_tested[i] * base);
		base *= 10;
	}
		
	return val;
}

int main()
{
	int number;
	cin >> number;
	int num_loaded{ 0 };
	num_tested[0] = 1;
	len = 1;
	while (Cal() <= number)
	{
		++num_loaded;
		AddOne();
	}
	cout << num_loaded << endl;
	return 0;
}