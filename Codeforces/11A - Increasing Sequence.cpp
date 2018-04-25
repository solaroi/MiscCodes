#include<iostream>
using namespace std;

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	
	int len, d;
	cin >> len >> d;
	int *seq = new int[len];
	for (int i = 0; i < len; ++i)
		cin >> seq[i];
	int num_moves{ 0 };
	for (int i = 0; i < len - 1; ++i)
	{
		if (seq[i] >= seq[i + 1])
		{
			int x = (seq[i] - seq[i + 1]) / d + 1;
			seq[i + 1] += x*d;
			num_moves += x;
		}	
	}
	cout << num_moves << endl;
	return 0;
}


