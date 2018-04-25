#include<iostream>
//#include<cmath> //abs() of int is in stdlib.h which could be loaded by using std, while float version is defined in cmath
using namespace std;

const int int_max = 2000000000;
int num_requests, len_square;
int x_center, y_center;
int square[100][100];

int Remoteness(int row_num, int &left, int &right)
{
	int distance{ 0 };
	for (int i = left; i <= right; ++i)
		distance += abs(i - y_center) + abs(row_num - x_center);
	return distance;
}

int BestInRow(int row_num, int num_men, int &left, int &right)
{
	int left_bound{ y_center }, right_bound{ y_center };
	if (square[row_num][y_center] == 0)
	{
		left = y_center - num_men / 2;
		right = y_center + (num_men - 1) / 2;
		return Remoteness(row_num, left, right);
	}
	while (square[row_num][left_bound] == 1)
		--left_bound;
	while (square[row_num][right_bound] == 1)
		++right_bound;
	bool left_prio_right = abs(left_bound - y_center) <= abs(right_bound - y_center);
	if (left_bound >= num_men && left_prio_right)
	{
		left = left_bound - num_men + 1; right = left_bound;
		return Remoteness(row_num, left, right);
			
	}
	else if (right_bound <= len_square - num_men + 1)
	{
		left = right_bound; right = right_bound + num_men - 1;
		return Remoteness(row_num, left, right);
	}
	return -1;
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	
	cin >> num_requests >> len_square;
	x_center = (len_square + 1) / 2; y_center = x_center;
	int num_men, left, right;
	
	for (int i = 0; i < num_requests; ++i)
	{
		cin >> num_men;
		int min_dis{ int_max }, best_row{ 100 }, best_left, best_right;
		for (int num_row = 1; num_row <= len_square; ++num_row)
		{
			int remoteness = BestInRow(num_row, num_men, left, right);
			if (remoteness >= 0)
			{
				if (remoteness == min_dis && num_row < best_row)
				{
					best_row = num_row;
					best_left = left; best_right = right;
				}
				else if (remoteness < min_dis)
				{
					min_dis = remoteness;
					best_row = num_row;
					best_left = left; best_right = right;
				}
			}
		}
		if (min_dis < int_max)
		{
			for (int i = best_left; i <= best_right; ++i)
				square[best_row][i] = 1;
			cout << best_row << ' ' << best_left << ' ' << best_right << endl;
		}
		else cout << -1 << endl;
	}
		


	
	return 0;
}


