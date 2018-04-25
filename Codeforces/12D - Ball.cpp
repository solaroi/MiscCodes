#include<iostream>
#include<algorithm>
using namespace std;
#define maxn 5000001

struct Lady
{
	int beauty, intellect, richness;
};
int num_ladies;
Lady ladies[maxn];
//segment tree: stores the largest richness value for an interval of intellect
//intellect value is discreted into 1, 2, ..., num_intellect
//every leaf segtree[i] stores the largest richness of 
//those ladies who has been inserted and with intellect value i
int segtree[maxn >> 2];

inline bool compare(Lady l1, Lady l2)
{
	return l1.beauty > l2.beauty;
}

void insert(int root, int left, int right, int pos, int val)
{
	if (left == right)
	{
		segtree[root] = max(val, segtree[root]);
		return;
	}
	int mid = (left + right) >> 1, leftchild = root << 1, rightchild = leftchild | 1;
	if (pos <= mid)
		insert(leftchild, left, mid, pos, val);
	else insert(rightchild, mid + 1, right, pos, val);
	segtree[root] = max(segtree[leftchild], segtree[rightchild]);
}

int query(int root, int left, int right, int qleft, int qright)
{
	if (left >= qleft&&right <= qright)
		return segtree[root];
	int mid = (left + right) >> 1, leftchild = root << 1, rightchild = leftchild | 1;
	int val{ 0 };
	if (qleft <= mid)
		val = max(val, query(leftchild, left, mid, qleft, qright));
	if (qright > mid)
		val = max(val, query(rightchild, mid + 1, right, qleft, qright));
	return val;
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);

	cin >> num_ladies;
	for (int i = 0; i < num_ladies; ++i)
		cin >> ladies[i].beauty;
	for (int i = 0; i < num_ladies; ++i)
		cin >> ladies[i].intellect;
	for (int i = 0; i < num_ladies; ++i)
		cin >> ladies[i].richness;
	//discrete intellect 
	int *sorted_intellect = new int[num_ladies];
	for (int i = 0; i < num_ladies; ++i)
		sorted_intellect[i] = ladies[i].intellect;
	sort(sorted_intellect, sorted_intellect + num_ladies);
	int num_intellect = unique(sorted_intellect, sorted_intellect + num_ladies) - sorted_intellect;
	for (int i = 0; i < num_ladies; ++i)
		ladies[i].intellect = lower_bound(sorted_intellect, sorted_intellect + num_intellect, ladies[i].intellect) - sorted_intellect + 1;
	sort(ladies, ladies + num_ladies, compare);
	int num_suicide{ 0 };
	int j{ 0 };
	for (int i = 0; i < num_ladies; i=j)
	{
		//for ladies who have the same beauty, just find if they will commit suicide by comparing with 
		//those with larger beauty value, which has been inserted into the segtree before
		for (j = i; ladies[j].beauty == ladies[i].beauty && j < num_ladies; ++j)
			if (query(1, 1, num_intellect, ladies[j].intellect + 1, num_intellect + 1) > ladies[j].richness)
				++num_suicide;
		//lady i to lady j-1 have the same beauty, insert them into segtree to update
		for (int k = i; k < j; ++k)
			insert(1, 1, num_intellect, ladies[k].intellect, ladies[k].richness);
	}
	cout << num_suicide << endl;
	return 0;
}


