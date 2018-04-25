#include <iostream>
using namespace std;

int dis[25][25];
int obj[25][2];
int x_bag, y_bag, num;

int Distance(int x1, int y1, int x2, int y2)
{
	return (x1 - x2)*(x1 - x2) + (y1 - y2)*(y1 - y2);
}

int dp(int state, int *len, int *state_path)
{
	if (len[state] != -1)
		return len[state];
	int min{ 200000000 }, best_state;
	for (int i = 1; i <= num; ++i)
	{
		int mask1 = 1 << (i - 1);
		if (state&mask1)
		{
			int sub_state1 = state&(~mask1);
			int l1 = dp(sub_state1, len, state_path) + 2 * dis[0][i];
			if (l1 < min)
			{
				min = l1;
				best_state = sub_state1;
			}
			for (int j = i + 1; j <= num; ++j)
			{
				int mask2 = 1 << (j - 1);
				if (state&mask2)
				{
					int sub_state2 = sub_state1&(~mask2);
					int l2 = dp(sub_state2, len, state_path) + dis[0][i] + dis[0][j] + dis[i][j];
					if (l2 < min)
					{
						min = l2;
						best_state = sub_state2;
					}
				}
			}
			break;
		}
	}
	len[state] = min;
	state_path[state] = best_state;
	return min;
}

int main()
{
	std::ios::sync_with_stdio(false);
	cin.tie(0);

	cin >> x_bag >> y_bag >> num;
	int x, y;
	for (int i = 1; i <= num; ++i)
	{
		cin >> x >> y;
		obj[i][0] = x; obj[i][1] = y;
		dis[0][i] = Distance(x_bag, y_bag, x, y); dis[i][0] = dis[0][i];
		for (int j = 1; j < i; ++j)
		{
			dis[j][i] = Distance(obj[j][0], obj[j][1], x, y);
			dis[i][j] = dis[j][i];
		}
	}
	int max_state = (1 << num) - 1;
	int *len = new int[max_state + 1], *state_path = new int[max_state + 1];
	for (int i = 1; i <= max_state; ++i)
		len[i] = -1;
	len[0] = 0;

	int l = dp(max_state, len, state_path);

	cout << l << endl;

	for (int i = max_state; i != 0; i = state_path[i])
	{
		cout << 0 << ' ';
		int diff = i - state_path[i];
		int mask{ 1 }, obj_num{ 0 };
		for (int j = 1; j <= num; ++j)
		{
			if (int(diff&mask) != 0)
			{
				++obj_num;
				cout << j << ' ';
				if (obj_num >= 2)
					break;
			}
			mask *= 2;
		}
	}
	cout << 0 << endl;
	return 0;
}





//#include <iostream>
//using namespace std;
//
//const int int_max = 2000000000;
//int dis[25][25];
//int obj[25][2];
//int x_bag, y_bag, num;
//
//int Distance(int x1, int y1, int x2, int y2)
//{
//	return (x1 - x2)*(x1 - x2) + (y1 - y2)*(y1 - y2);
//}
//
//
//int main()
//{
//	std::ios::sync_with_stdio(false);
//	cin.tie(0);
//
//	cin >> x_bag >> y_bag >> num;
//	int x, y;
//	for (int i = 1; i <= num; ++i)
//	{
//		cin >> x >> y;
//		obj[i][0] = x; obj[i][1] = y;
//		dis[0][i] = Distance(x_bag, y_bag, x, y); dis[i][0] = dis[0][i];
//		for (int j = 1; j < i; ++j)
//		{
//			dis[j][i] = Distance(obj[j][0], obj[j][1], x, y);
//			dis[i][j] = dis[j][i];
//		}
//	}
//	int max_state = (1 << num) - 1;
//	int *len = new int[max_state + 1], *state_path = new int[max_state + 1];
//	for (int i = 1; i <= max_state; ++i)
//		len[i] = int_max;
//	len[0] = 0;
//	
//	
//	for (int state = 0; state <= max_state; ++state)
//	{
//		if (len[state] != int_max)
//		{
//			for (int j = 1; j <= num; ++j)
//			{
//				int mask1 = 1 << (j - 1);
//				if (!(state&mask1))
//				{
//					int new_state1 = state | mask1;
//					int l1 = len[state] + 2 * dis[0][j];
//					if (l1 < len[new_state1])
//					{
//						len[new_state1] = l1;
//						state_path[new_state1] = state;
//					}
//					for (int k = j + 1; k <= num; ++k)
//					{
//						int mask2 = 1 << (k - 1);
//						if (!(state&mask2))
//						{
//							int new_state2 = new_state1 | mask2;
//							int l2 = len[state] + dis[0][j] + dis[0][k] + dis[j][k];
//							if (l2 < len[new_state2])
//							{
//								len[new_state2] = l2;
//								state_path[new_state2] = state;
//							}
//						}
//					}
//					break;
//				}
//			}
//		}
//	}
//
//	cout << len[max_state] << endl;
//	for (int i = max_state; i != 0; i = state_path[i])
//	{
//		cout << 0 << ' ';
//		int diff = i - state_path[i];
//		int mask{ 1 }, obj_num{ 0 };
//		for (int j = 1; j <= num; ++j)
//		{
//			if (int(diff&mask) != 0)
//			{
//				++obj_num;
//				cout << j << ' ';
//				if (obj_num >= 2)
//					break;
//			}
//			mask *= 2;
//		}
//	}
//	cout << 0 << endl;
//	return 0;
//}