#include<iostream>
#include<algorithm>
using namespace std;
using ll = long long;
ll inf = 1LL << 62;
int len, seq[5000];
//steps[5000][5000]: steps[i][j] refers to the minimum steps for converting seq[0:i] into non-decreasing sequence
//with seq[i] = sorted[j]
//hence, steps[i][j] = min{steps[i-1][k]}+abs(seq[i]-sorted[j]), k=1,2,...,j
//obiviously, steps[i][j] can be calculated by knowing only the former state: steps[i-1][k], k=1,2,...,j
//as it's impossible and unnecessary to declare an array of 5000x5000, we only need to rolling in the space of 2 states to get the result
ll steps[2][5000];

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);

	cin >> len;
	int *sorted = new int[len];
	for (int i = 0; i < len; ++i)
	{
		cin >> seq[i];
		sorted[i] = seq[i];
	}
	sort(sorted, sorted + len);
	int num_unique = unique(sorted, sorted + len) - sorted;
	for (int i = 0; i < num_unique; ++i)
		steps[0][i] = abs(seq[0] - sorted[i]);
	int current = 1;
	for (int i = 1; i < len; ++i)
	{
		ll minlast = inf;
		for (int j = 0; j < num_unique; ++j)
		{
			minlast = min(steps[current ^ 1][j], minlast);
			steps[current][j] = minlast + abs(seq[i] - sorted[j]);
		}
		current ^= 1;
	}
	current ^= 1;
	ll minsteps = inf;
	for (int i = 0; i < num_unique; ++i)
		if (steps[current][i] < minsteps)
			minsteps = steps[current][i];
	cout << minsteps << endl;
	return 0;
}
