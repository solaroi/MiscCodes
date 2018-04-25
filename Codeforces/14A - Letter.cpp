#include<iostream>
#include<algorithm>
using namespace std;

char sheet[50][50];

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);

	int num_rows, num_cols;
	cin >> num_rows >> num_cols;
	char square;
	cin.get(square);
	int min_rows{ 50 }, max_rows{ 0 }, min_cols{ 50 }, max_cols{ 0 };
	for (int i = 0; i < num_rows; ++i)
	{
		for (int j = 0; j < num_cols; ++j)
		{
			cin.get(square);
			sheet[i][j] = square;
			if (square == '*')
			{
				min_rows = min(i, min_rows);
				max_rows = max(i, max_rows);
				min_cols = min(j, min_cols);
				max_cols = max(j, max_cols);
			}
		}
		cin.get(square);
	}
	for (int i = min_rows; i <= max_rows; ++i)
	{
		for (int j = min_cols; j <= max_cols; ++j)
			cout << sheet[i][j];
		cout << endl;
	}
	return 0;
}
