//time limit: 2000ms
//time used:  1960ms
#include <iostream>
using namespace std;
typedef unsigned int uint;
uint matrix_size;
int pos_row0 = -1;
uint **matrix;
uint ***num;
char ***dir;

void init()
{
	matrix = new uint*[matrix_size];
	for (uint i = 0; i<matrix_size; ++i)
		matrix[i] = new uint[matrix_size];
	num = new uint**[matrix_size];
	for (uint i = 0; i < matrix_size; ++i)
	{
		num[i] = new uint*[matrix_size];
		for (uint j = 0; j < matrix_size; ++j)
			num[i][j] = new uint[2];
	}
	dir = new char**[matrix_size];
	for (uint i = 0; i < matrix_size; ++i)
	{
		dir[i] = new char*[matrix_size];
		for (uint j = 0; j < matrix_size; ++j)
			dir[i][j] = new char[2];
	}
}

void factor(uint x, uint &num2, uint &num5)
{
	if (x == 0)
	{
		num2 = 0; num5 = 0; return;
	}
	num2 = 0; num5 = 0;
	for (; x % 5 == 0; x = x / 5)
		++num5;
	for (; x % 2 == 0; x = x / 2)
		++num2;
}

void dp()
{
	uint num2, num5, num2_r, num2_c, num5_r, num5_c;
	factor(matrix[0][0], num2, num5);
	num[0][0][0] = num2;
	num[0][0][1] = num5;
	for (uint j = 1; j < matrix_size; ++j)
	{
		factor(matrix[0][j], num2, num5);
		num[0][j][0] = num2 + num[0][j - 1][0];
		num[0][j][1] = num5 + num[0][j - 1][1];
		dir[0][j][0] = 'R'; dir[0][j][1] = 'R';
	}
	for (uint i = 1; i < matrix_size; ++i)
	{
		factor(matrix[i][0], num2, num5);
		num[i][0][0] = num2 + num[i - 1][0][0];
		num[i][0][1] = num5 + num[i - 1][0][1];
		dir[i][0][0] = 'D'; dir[i][0][1] = 'D';
		for (uint j = 1; j < matrix_size; ++j)
		{
			factor(matrix[i][j], num2, num5);
			num2_r = num[i - 1][j][0], num2_c = num[i][j - 1][0];
			if (num2_r <= num2_c)
			{
				num[i][j][0] = num2 + num2_r; dir[i][j][0] = 'D';
			}
			else
			{
				num[i][j][0] = num2 + num2_c; dir[i][j][0] = 'R';
			}
			num5_r = num[i - 1][j][1], num5_c = num[i][j - 1][1];
			if (num5_r <= num5_c)
			{
				num[i][j][1] = num5 + num5_r; dir[i][j][1] = 'D';
			}
			else
			{
				num[i][j][1] = num5 + num5_c; dir[i][j][1] = 'R';
			}
		}
	}
}

int main()
{
	cin >> matrix_size;
	init();
	for (uint i = 0; i < matrix_size; ++i)
	{
		for (uint j = 0; j < matrix_size; ++j)
		{
			cin >> matrix[i][j];
			if (pos_row0 == -1 && matrix[i][j] == 0)
				pos_row0 = i;
		}

	}

	dp();
	bool two_prior_five = num[matrix_size - 1][matrix_size - 1][0] < num[matrix_size - 1][matrix_size - 1][1];
	uint min25 = two_prior_five ? num[matrix_size - 1][matrix_size - 1][0] : num[matrix_size - 1][matrix_size - 1][1];
	int two_or_five = two_prior_five ? 0 : 1;
	if (pos_row0 != -1 && min25 >= 1)
	{
		cout << 1 << endl;
		for (int i = 0; i < pos_row0; ++i)
			cout << 'D';
		for (uint i = 0; i < matrix_size - 1; ++i)
			cout << 'R';
		for (uint i = pos_row0; i < matrix_size - 1; ++i)
			cout << 'D';
		cout << endl;
	}
	else
	{
		char *direction = new char[2 * matrix_size - 1];
		direction[2 * matrix_size - 2] = '\0';
		uint row = matrix_size - 1, col = matrix_size - 1;
		uint i = 2 * matrix_size - 3;
		while (row != 0 || col != 0)
		{
			char d = dir[row][col][two_or_five];
			direction[i] = d;
			if (d == 'R')
				--col;
			if (d == 'D')
				--row;
			--i;
		}
		cout << min25 << endl << direction << endl;
	}
	return 0;
}


