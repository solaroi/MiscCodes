//Solution 1: dfs
#include <iostream>
using namespace std;
int n, a, b, *h, *num;
int least{ 2000000000 }, *path;//INT_MAX = 2^31 = 2*(2^10)^3 ~= 2*1000^3 = 2*10^9

void search(int pos, int left, int mid, int right)
{
	num[pos] = 0;
	if (pos == n - 1)
	{
		while (left >= 0 || mid >= 0 || right >= 0)
		{
			left -= b; mid -= a; right -= b;
			++num[n - 1];
		}
		int sum{ 0 };
		for (int i = 2; i < n; ++i)
			sum += num[i];
		if (sum < least)
		{
			least = sum;
			for (int i = 2; i < n; ++i)
				path[i] = num[i];
		}
		return;
	}
	while (left >= 0)
	{
		left -= b; mid -= a; right -= b;
		++num[pos];
	}
	while (mid >= 0)
	{
		search(pos + 1, mid, right, h[pos + 2]);
		mid -= a; right -= b;
		++num[pos];
	}
	search(pos + 1, mid, right, h[pos + 2]);
}

int main()
{
	std::ios::sync_with_stdio(false);
	cin.tie(0);
	cin >> n >> a >> b;
	h = new int[n + 1]; num = new int[n + 1]; path = new int[n + 1];
	for (int i = 1; i <= n; ++i)
		cin >> h[i];

	search(2, h[1], h[2], h[3]);

	cout << least << endl;
	for (int i = 2; i < n; ++i)
	{
		for (int j = 0; j < path[i]; ++j)
			cout << i << ' ';
	}
	cout << endl;
	return 0;
}

//Solution2: dp
//#include <iostream>
//using namespace std;
//
//const int int_max = 20000000;
//
//int main()
//{
//	std::ios::sync_with_stdio(false);
//	cin.tie(0);
//
//	int n, a, b;
//	cin >> n >> a >> b;
//	int *h = new int[n + 2]; h[n + 1] = 0;
//	for (auto i = 1; i <= n; ++i)
//	{
//		cin >> h[i];
//		h[i] += 1;
//	}
//
//	int dp[12][17][17][17], path[12][17][17][17];
//	for (auto i = 1; i <= n; ++i)
//	{
//		for (auto j = 0; j <= 16; ++j)
//		{
//			for (auto k = 0; k <= 16; ++k)
//			{
//				for (auto m = 0; m <= 16; ++m)
//					dp[i][j][k][m] = int_max;
//			}
//		}
//	}
//	dp[2][h[1]][h[2]][h[3]] = 0;
//	path[2][h[1]][h[2]][h[3]] = 0;
//	for (int i = 2; i <= n - 1; ++i)
//	{
//		for (int j = h[i - 1]; j >= 0; --j)
//		{
//			for (int k = h[i]; k >= 0; --k)
//			{
//				for (int l = h[i + 1]; l >= 0; --l)
//				{
//					if (dp[i][j][k][l] != int_max)
//					{
//						int a1 = j - b > 0 ? j - b : 0;
//						int a2 = k - a > 0 ? k - a : 0;
//						int a3 = l - b > 0 ? l - b : 0;
//						if (j == 0 && dp[i][j][k][l] < dp[i + 1][k][l][h[i + 2]])
//						{
//							dp[i + 1][k][l][h[i + 2]] = dp[i][j][k][l];
//							path[i + 1][k][l][h[i + 2]] = path[i][j][k][l];
//						}
//						if (a1 == 0 && dp[i][j][k][l] + 1 < dp[i + 1][a2][a3][h[i + 2]])
//						{
//							dp[i + 1][a2][a3][h[i + 2]] = dp[i][j][k][l] + 1;
//							path[i + 1][a2][a3][h[i + 2]] = i * 1000000 + j * 10000 + k * 100 + l;
//						}
//						if (dp[i][j][k][l] + 1 < dp[i][a1][a2][a3])
//						{
//							dp[i][a1][a2][a3] = dp[i][j][k][l] + 1;
//							path[i][a1][a2][a3] = i * 1000000 + j * 10000 + k * 100 + l;
//						}
//					}
//				}
//			}
//		}
//	}
//	cout << dp[n][0][0][0] << endl;
//	int i{ n }, j{ 0 }, k{ 0 }, l{ 0 }, p = path[i][j][k][l];
//	while (!(i == 2 && j == h[1] && k == h[2] && l == h[3]))
//	{
//		i = p / 1000000;
//		j = (p - i * 1000000) / 10000;
//		k = (p - i * 1000000 - j * 10000) / 100;
//		l = p - i * 1000000 - j * 10000 - k * 100;
//		cout << i << ' ';
//		p = path[i][j][k][l];
//	}
//	cout << endl;
//	return 0;
//}