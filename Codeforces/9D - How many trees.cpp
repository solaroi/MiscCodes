#include<iostream>
#include<algorithm>
using namespace std;

typedef unsigned long long unll;
unll  num_trees[36][36];

unll NumTrees(int height, int num)
{
	if (num_trees[height][num] != -1)
		return num_trees[height][num];
	if (num < height)
		return 0;
	if (num <= 1)
		return 1;
	unll rslt{ 0 };
	for (int i = 1; i <= num; ++i)
	{
		int new_height = max(height - 1, 0);//when height = 0, its sub-tree's restrictive height could be set to 0
		unll lh = NumTrees(new_height, i - 1);
		unll rh = NumTrees(new_height, num - i);
		rslt += (lh*NumTrees(0, num - i) + rh*NumTrees(0, i - 1) - lh*rh);
	}
	num_trees[height][num] = rslt;
	return rslt;
}

int main()
{
	int num_nodes, height;
	cin >> num_nodes >> height;
	for (int i = 0; i < 36; ++i)
		for (int j = 0; j < 36; ++j)
			num_trees[i][j] = -1;
	cout << NumTrees(height, num_nodes) << endl;
	return 0;
}


//#include<iostream>
//#include<algorithm>
//using namespace std;
//
//typedef unsigned long long unll;
//
//int main()
//{
//	int num_nodes, height;
//	cin >> num_nodes >> height;
//	unll **num_trees = new unll*[height + 1];
//	for (int h = 0; h < height; ++h)
//		num_trees[h] = new unll[num_nodes];
//
//	num_trees[0][0] = 1;
//	for (int h = 1; h < height; ++h)
//		num_trees[h][0] = 0;
//
//	for (int h = 0; h < height; ++h)
//	{
//		int len = num_nodes - (height - h) + 1;
//		for (int n = 1; n < len; ++n)
//		{
//			if (n < h)
//			{
//				num_trees[h][n] = 0;
//				continue;
//			}
//			int new_height = max(h - 1, 0);
//			unll sum{ 0 };
//			for (int num_left_child = 0; num_left_child <= n - 1; ++num_left_child)
//			{
//				sum += (num_trees[new_height][num_left_child] * num_trees[0][n - 1 - num_left_child]\
//					+ num_trees[new_height][n - 1 - num_left_child] * num_trees[0][num_left_child]\
//					- num_trees[new_height][num_left_child] * num_trees[new_height][n - 1 - num_left_child]);
//			}
//			num_trees[h][n] = sum;
//		}
//	}
//	unll rslt{ 0 };
//	int new_height = max(height - 1, 0);
//	for (int num_left_child = 0; num_left_child <= num_nodes - 1; ++num_left_child)
//	{
//		rslt += (num_trees[new_height][num_left_child] * num_trees[0][num_nodes - 1 - num_left_child]\
//			+ num_trees[new_height][num_nodes - 1 - num_left_child] * num_trees[0][num_left_child]\
//			- num_trees[new_height][num_left_child] * num_trees[new_height][num_nodes - 1 - num_left_child]);
//	}
//	cout << rslt << endl;
//	return 0;
//}