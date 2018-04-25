
#include <iostream>
#include <string>
#include <cmath>
using namespace std;

string diag[4]{ "RU","RD", "LD", "LU" };
string direct[4]{ "R","D","L","U" };
int main()
{

	string start, dest;
	cin >> start >> dest;
	short start_row = start[1] - '0', start_col = start[0] - 'a' + 1;
	short end_row = dest[1] - '0', end_col = dest[0] - 'a' + 1;
	short dist_row = abs(start_row - end_row), dist_col = abs(start_col - end_col);
	short diag_num = dist_row < dist_col ? dist_row : dist_col;
	short direct_num = abs(dist_row - dist_col);
	short diag_idx, direct_idx;
	if (end_row > start_row)
	{
		if (end_col > start_col)
		{
			diag_idx = 0; 
			direct_idx = dist_row < dist_col ? 0 : 3;
		}
		else
		{
			diag_idx = 3;
			direct_idx = dist_row < dist_col ? 2 : 3;
		}
	}
	else
	{
		if (end_col > start_col)
		{
			diag_idx = 1;
			direct_idx = dist_row < dist_col ? 0 : 1;
		}
		else
		{
			diag_idx = 2;
			direct_idx = dist_row < dist_col ? 2 : 1;
		}
	}
	cout << diag_num + direct_num << endl;
	for (short i = 0; i < diag_num; ++i)
		cout << diag[diag_idx] << endl;
	for (short i = 0; i < direct_num; ++i)
		cout << direct[direct_idx] << endl;
	return 0;
}


