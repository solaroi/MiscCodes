#include <iostream>
#include <fstream> 
#include <sstream> 
#include <array>
#include <string>
#include <vector>
#include <deque>
#include <list>
#include <map>
#include <algorithm>
#include <cmath>
#include <iterator>
#include <ctime>
using namespace std;
int main()
{
	string str;
	while (true)
	{
		cin >> str;
		if (str == "0")
			break;
		str = "0" + str;
		vector<int> counter;
		counter.resize(str.length() + 5);
		counter[0] = 1;
		int i = 1;
		while (i < str.length())
		{
			if (str[i] == '0')
			{
				counter[i] = counter[i - 2]; counter[i + 1] = counter[i];
				i = i + 2; continue;
			}
			else if (str[i - 1] == '1' || (str[i - 1] == '2' && str[i] <= '6' && str[i] >= '1'))
				counter[i] = counter[i - 1] + counter[i - 2];
			else counter[i] = counter[i - 1]; 
			++i;
		}
		cout << counter[i - 1] << endl;
	}
	return 0;
}

