
#include <iostream>
#include <string>
using namespace std;

char grid[3][3];

bool win(char c)
{
	for (auto i = 0; i < 3; ++i)
	{
		if (grid[i][0] == c&&grid[i][1] == c&&grid[i][2] == c)
			return true;
		if (grid[0][i] == c&&grid[1][i] == c&&grid[2][i] == c)
			return true;
	}
	if ((grid[0][0] == c&&grid[1][1] == c&&grid[2][2] == c) || (grid[2][0] == c&&grid[1][1] == c&&grid[0][2] == c))
		return true;
	return false;
}

int main()
{
	short num_x{ 0 }, num_0{ 0 };
	for (auto i = 0; i < 3; ++i)
	{
		for (auto j = 0; j < 3; ++j)
		{
			cin >> grid[i][j];
			if (grid[i][j] == 'X')
				++num_x;
			else if (grid[i][j] == '0')
				++num_0;
		}
	}
	
	if (num_0 > num_x || num_x > num_0 + 1)
		cout << "illegal" << endl;
	else
	{
		bool winx = win('X'), win0 = win('0');
		if (num_0 == num_x)
		{
			if (winx)
				cout << "illegal" << endl;
			else if (win0)
				cout << "the second player won" << endl;
			else cout << "first" << endl;
		}
		else 
		{
			if (win0)
				cout << "illegal" << endl;
			else if (winx)
				cout << "the first player won" << endl;
			else if ((num_0 + num_x) == 9)
				cout << "draw" << endl;
			else cout << "second" << endl;
		}
	}
	return 0;
}

