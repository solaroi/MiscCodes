
#include <iostream>
#include <fstream> 
#include <sstream> 
#include <deque>
#include <string>
#include <vector>
#include <cmath>
using namespace std;

bool IsPrime(long long x)
{
	long long end = (long long)(sqrt(x));
	for(long long i = 2; i <= end; ++i)
	{
		if (x % i == 0)
			return false;
	}
	return true;
}

//get Factorization of x, store the prime divisors into v
vector<long long> Factorization(long long x)
{
	vector<long long> rslt;
	long long i = 2;
	long long end = (long long)(sqrt(x));
	while (i <= end)
	{
		if (x % i == 0)
		{
			rslt.push_back(i);
			x = x / i;
			end = (long long)(sqrt(x));
			i = i - 2;
		}
		++i;
	}
	rslt.push_back(x);
	return rslt;
}

int main()
{
	//the description of the problem's input is wrong: not in a.in, instead in std
	//fstream input("a.in");
	int a;
	cin >> a;
	vector<int> PrimeIndex;
	for (auto i = 0; i <= a; ++i)
	{
		if (IsPrime(i))
			PrimeIndex.push_back(i);
	}

	for (auto i : PrimeIndex)
	{
		/*if (i == 61)
			continue;*/
		long long num = (long long)(pow(2, i)) - 1;
		//cout << fixed << i << " " << num + 1 << endl;
		vector<long long> factor;
		factor = Factorization(num);
		if (factor.size() > 1)
		{
			cout << factor[0];
			for (size_t j = 1; j < factor.size(); ++j)
				cout << " * " << factor[j];
			cout << " = " << num << " = " << "( 2 ^ " << i << " ) - 1" << endl;
		}
	}
	return 0;
}
