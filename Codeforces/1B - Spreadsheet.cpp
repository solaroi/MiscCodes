
#include <iostream>
#include <string>
#include <sstream>
#include <cmath>
#include <algorithm>
using namespace std;

long ab2num(const string &str)
{
	int digits = 0;
	long rslt = 0;
	for (auto ritr = str.crbegin(); ritr != str.crend(); ++ritr)
	{
		int num = *ritr - 'A' + 1;
		rslt = num*long(pow(26, digits)) + rslt;
		++digits;
	}
	return rslt;
}

string &num2ab(const long &num)
{
	string *rslt = new string;
	long quio = num;
	while (quio > 26)
	{
		if (quio % 26 == 0)
		{
			*rslt = 'Z' + (*rslt);
			quio = (quio - 26) / 26;
			continue;
		}
		*rslt = char(quio % 26 - 1 + 'A') + (*rslt);
		quio = quio / 26;
	}
	*rslt = char(quio - 1 + 'A') + (*rslt);
	return *rslt;
}

int main()
{
	long test_number;
	cin >> test_number;
	for (auto i = 0; i < test_number; ++i)
	{
		string str;
		cin >> str;
		auto C_pos = str.find('C');
		if (C_pos != string::npos && C_pos > 0 && str[C_pos - 1] >= '0' && str[C_pos - 1] <= '9')
		{
			string row_str = str.substr(1, C_pos - 1);
			stringstream col(str.substr(C_pos + 1, 10000));
			long col_num; col >> col_num;
			string col_str = num2ab(col_num);
			cout << col_str << row_str << endl;
		}
		else
		{
			auto row_pos = find_if(str.cbegin(), str.cend(), [](char c) {return c >= '0' && c <= '9'; });
			string col_str = str.substr(0, distance(str.cbegin(), row_pos));
			long col_num = ab2num(col_str);
			string row_str = str.substr(distance(str.cbegin(), row_pos), 10000);
			cout << 'R' << row_str << 'C' << col_num << endl;
		}
	}
	return 0;
}