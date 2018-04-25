#include <iostream>
#include <string>
#include <vector>
#include <map>
using namespace std;

int n;
map<string, char> macro;

char search(string &expr, int left, int right)
 {
	char suspecious{ '0' };
	int level{ 0 }, first;
	for (int i = left; i <= right; ++i)
	{
		char c = expr[i];
		if (level > 0)
		{
			if (c == '(')
				++level;
			else if (c == ')')
			{
				--level;
				if (level == 0)
				{
					if (search(expr, first, i - 1) == '3')
						return '3';
				}
			}
		}
		else if (c == '(')
		{
			level = 1;
			first = i + 1;
		}
		else if (c == '3')
			return '3';
		else if (c == '+')
			suspecious = '2';
		else if (c == '-')
		{
			if (expr[i + 1] == '2' && (i == right - 1 || expr[i + 2] == '-' || expr[i + 2] == '+'))
				return '3';
			suspecious = '2';
		}
		else if (c == '*')
		{
			if (expr[i - 1] == '2' || expr[i + 1] == '2')
				return '3';
			if (suspecious < '1')
				suspecious = '1';
		}
		else if (c == '/')
		{
			if (expr[i - 1] == '2' || expr[i + 1] == '2' || expr[i + 1] == '1')
				return '3';
			if (suspecious < '1')
				suspecious = '1';
		}
	}
	return suspecious;
}

void input(string &macro_value)
{
	string var;
	char x;
	while (true)
	{
		cin.get(x);
		if (x == '\n')
			break;
		else if (x == ' ')
			continue;
		else if (x == '+' || x == '-' || x == '*' || x == '/' || x == '(' || x == ')')
		{
			if (!var.empty())
			{
				if (macro.find(var) == macro.end())
					macro_value.push_back('$');
				else macro_value.push_back(macro[var]);
				var.clear();
			}
			macro_value.push_back(x);
		}
		else var.push_back(x);
	}
	if (!var.empty())
	{
		if (macro.find(var) == macro.end())
			macro_value.push_back('$');
		else macro_value.push_back(macro[var]);
		var.clear();
	}
}


int main()
{
	
	std::ios::sync_with_stdio(false);
	cin.tie(0);

	cin >> n;
	string in_str;
	char x{ ' ' };
	for(int i=0;i<n;++i)
	{ 
		cin >> in_str;
		if (in_str == "#")
			cin >> in_str;
		string macro_name; 
		cin >> macro_name;
		string macro_value;
		input(macro_value);
		x = search(macro_value, 0, macro_value.size() - 1);
		macro[macro_name] = x;
	}
	string expr;
	input(expr);
	x = search(expr, 0, expr.size() - 1);
	if (x == '3')
		cout << "Suspicious" << endl;
	else cout << "OK" << endl;
	return 0;
}
