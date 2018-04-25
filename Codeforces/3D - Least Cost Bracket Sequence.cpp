
#include <iostream>
#include <string>
#include <set>
#include <array>
using namespace std;

int main()
{
	string in_str;
	cin >> in_str;
	long str_len = in_str.size();
	char *c_str = new char[str_len+1];
	set<array<long, 2>> left_minus_right;
	long cnt{ 0 };
	long long cost{ 0 };
	for (long i = 0; i<str_len; ++i)
	{
		char c = in_str[i];
		c_str[i] = c;
		if (c == '?')
		{
			c_str[i] = ')';
			--cnt;
			long l, r;
			cin >> l >> r;
			left_minus_right.insert({ l - r,i });
			cost = cost + r;
		}
		else if (c == '(')
			++cnt;
		else --cnt;
		if (cnt < 0)
		{
			if (left_minus_right.empty())
			{
				cout << -1 << endl; return 0;
			}
			long val = (*left_minus_right.begin())[0], pos = (*left_minus_right.begin())[1];
			c_str[pos] = '(';
			cost = cost + val;
			cnt = cnt + 2;
			left_minus_right.erase(left_minus_right.begin());
		}
	}
	if (cnt != 0)
		cout << -1 << endl;
	else
	{
		c_str[str_len] = '\0';
		cout << cost << endl << c_str << endl;
	}
	return 0;
}

