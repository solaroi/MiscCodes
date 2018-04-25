#include <iostream>
using namespace std;


int main()
{
	std::ios::sync_with_stdio(false);
	cin.tie(0);

	char chessboard[8][8];
	for (int i = 0; i < 8; ++i)
		for (int j = 0; j < 8; ++j)
			cin >> chessboard[i][j];

	int num{ 0 };
	for (int j = 0; j < 8; ++j)
	{
		if (chessboard[0][j] == 'B')
		{
			bool all_black{ true };
			for (auto k = 0; k < 8; ++k)
			{
				if (chessboard[k][j] != 'B')
				{
					all_black = false;
				}
			}
			if (all_black)
				++num;
		}
	}
	if (num == 8)
	{
		cout << 8 << endl; return 0;
	}
	for (int i = 0; i < 8; ++i)
	{
		if (chessboard[i][0] == 'B')
		{
			bool all_black{ true };
			for (auto k = 0; k < 8; ++k)
			{
				if (chessboard[i][k] != 'B')
				{
					all_black = false;
				}
			}
			if (all_black)
				++num;
		}
	}
	cout << num << endl;
	return 0;
}
