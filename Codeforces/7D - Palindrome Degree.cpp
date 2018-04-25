#include <iostream>
#include <string>
using namespace std;

//solution1: hash
int main()
{
	
	std::ios::sync_with_stdio(false);
	cin.tie(0);

	string str;
	cin >> str;

	int len = str.size();
	int *str_num = new int[len];
	for (int i = 0; i < len; ++i)
	{
		char c = str[i];
		if (c >= '0'&&c <= '9')
			str_num[i] = c - '0';
		else if (c >= 'A'&&c <= 'Z')
			str_num[i] = c - 'A' + 10;
		else if (c >= 'a'&&c <= 'z')
			str_num[i] = c - 'a' + 36;
	}
	int sum{ 0 }, base = 67;//
	int *degree = new int[len + 1];
	degree[0] = 0;
	int decimal_lr{ 0 }, decimal_rl{ 0 }, n{ 1 };
	for (int i = 0; i < len; ++i)
	{
		decimal_lr = decimal_lr + str_num[i]*n;
		decimal_rl = decimal_rl*base + str_num[i];
		n *= base;
		if (decimal_lr == decimal_rl)
			degree[i + 1] = degree[(i + 1) / 2] + 1;
		else degree[i + 1] = 0;
		sum += degree[i + 1];
	}
	cout << sum << '\n';
	return 0;
}

//solution 2: manancher
/*
#include <iostream>
#include <string>
using namespace std;

int main()
{
	
	std::ios::sync_with_stdio(false);
	cin.tie(0);

	string str;
	cin >> str;

	int len = str.size();
	char *expanded_str = new char[2 * len + 2];
	expanded_str[0] = '$'; expanded_str[1] = '#';
	for (int i = 1; i <= len; ++i)
	{
		expanded_str[2 * i] = str[i - 1];
		expanded_str[2 * i + 1] = '#';
	}
	int *max_palindrome = new int[2 * len + 2];
	max_palindrome[0] = 1;
	int last_max_center{ 0 }, right_bound{ 0 };
	for (int i = 1; i < len + 2; ++i) //only max_palindrome[2:len+1] is useful
	{
		if (i < right_bound)
		{
			int symmetry = 2 * last_max_center - i;
			max_palindrome[i] = max_palindrome[symmetry] < right_bound - i ? max_palindrome[symmetry] : right_bound - i;
		}
		else max_palindrome[i] = 1;
		while (expanded_str[i - max_palindrome[i]] == expanded_str[i + max_palindrome[i]])
			++max_palindrome[i];
		if (max_palindrome[i] + i > right_bound)
		{
			last_max_center = i;
			right_bound = max_palindrome[i] + i;
		}
	}
	int sum{ 1 }, *degree = new int[len];
	degree[0] = 1;
	for (int i = 1; i < len; ++i)
	{
		if (max_palindrome[i + 2] >= i + 2)
		{
		    degree[i] = degree[(i - 1) / 2] + 1;
		    sum += degree[i];
		}
		else degree[i] = 0;
	}
	cout << sum << '\n';
	return 0;
}
*/
