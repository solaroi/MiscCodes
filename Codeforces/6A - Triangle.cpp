#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
typedef unsigned short unshort;
int main()
{
	unshort sticks[4];
	cin >> sticks[0];
	for (auto i = 1; i < 4; ++i)
	{
		unshort len;
		cin >> len;
		auto j = i - 1;
		for (; j >= 0; --j)
		{
			if (sticks[j] < len)
				sticks[j + 1] = sticks[j];
			else
				break;
		}
		sticks[j + 1] = len;
	}
	if (sticks[0] > sticks[1] + sticks[2])
	{
		if (sticks[1] > sticks[2] + sticks[3])
			cout << "IMPOSSIBLE" << endl;
		else if (sticks[1] == sticks[2] + sticks[3])
			cout << "SEGMENT " << endl;
		else cout << "TRIANGLE" << endl;
	}
	else if(sticks[0] < sticks[1] + sticks[2])
		cout << "TRIANGLE" << endl;
	else
	{
		if (sticks[1] < sticks[2] + sticks[3])
			cout << "TRIANGLE " << endl;
		else cout << "SEGMENT" << endl;
	}
	return 0;
}