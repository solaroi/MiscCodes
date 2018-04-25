#include<iostream>
using namespace std;

typedef long long ll;
ll num_dc[10];

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	
	ll range;
	cin >> range;
	ll num_wrong_examples{ 0 };
	for (ll c = 1; c <= range; ++c)
	{
		++num_dc[c % 9 == 0 ? 9 : c % 9];
		num_wrong_examples -= range / c;
	}
	for (ll da = 1; da <= 9; ++da)
		for (ll db = 1; db <= 9; ++db)
			num_wrong_examples += num_dc[da] * num_dc[db] * num_dc[da*db % 9 == 0 ? 9 : da*db % 9];
	cout << num_wrong_examples << endl;

	return 0;
}


