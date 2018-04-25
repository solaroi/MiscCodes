
#include <iterator>
#include <vector>
#include <array>
#include <deque>
#include <map>
#include <list>
#include <iostream>
#include <fstream>
#include <random>
#include <algorithm>
#include <string>
#include <sstream>
using namespace std;

int main()
{
	int NumCols;
	vector<string> S;
	string str;
	while (cin >> NumCols)
	{
		if (NumCols == 0)
			break;
		cin >> str;
		int NumRows = str.size() / NumCols;
		S.clear();
		S.resize(NumRows);
		for (auto i = 0; i < NumRows; ++i)
			S[i] = str.substr(i*NumCols, NumCols);
		for (auto i = 1; i < NumRows; i = i + 2)
			reverse(S[i].begin(), S[i].end());
		for (auto j = 0; j < NumCols; ++j)
		{
			for (auto i = 0; i < NumRows; ++i)
				cout << S[i][j];
		}
		cout << endl;
	}
	return 0;
}