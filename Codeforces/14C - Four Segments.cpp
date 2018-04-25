#include<iostream>
#include<algorithm>
using namespace std;

struct Point
{
	int x_, y_;
	Point() = default;
	Point(int x, int y) :x_(x), y_(y) {};
	bool operator ==(Point &p) { return x_ == p.x_&&y_ == p.y_; };
};

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	Point p[4][2];
	
	for (int i = 0; i < 4; ++i)
		cin >> p[i][0].x_ >> p[i][0].y_ >> p[i][1].x_ >> p[i][1].y_;
	//get the index of 2 vertical and 2 horizontal
	int horizontal[2], vertical[2];
	int h = 0, v = 0;
	for (int i = 0; i < 4; ++i)
	{
		if (p[i][0] == p[i][1])
		{
			cout << "NO" << endl; 
			return 0;
		}
		else if (p[i][0].x_ == p[i][1].x_)
		{
			vertical[v] = i;
			++v;
			//make sure the direction of any vertical p[v][0]->p[v][1] is in +y 
			if (p[i][0].y_ > p[i][1].y_)
				swap(p[i][0], p[i][1]);
		}
		else if (p[i][0].y_ == p[i][1].y_)
		{
			horizontal[h] = i;
			++h;
			//make sure the direction of any horizontal p[h][0]->p[h][1] is in +x 
			if (p[i][0].x_ > p[i][1].x_)
				swap(p[i][0], p[i][1]);
		}
		else 
		{
			cout << "NO" << endl;
			return 0;
		}
	}
	//if not 2 vetical and 2 horizontal, NO
	if (v != 2 || h != 2)
	{
		cout << "NO" << endl;
		return 0;
	}
	int h1 = horizontal[0], h2 = horizontal[1];
	int v1 = vertical[0], v2 = vertical[1];
	//if 2 vertical or 2 horizontal are in the same line, NO
	if (p[h1][0].y_ == p[h2][0].y_ || p[v1][0].x_== p[v2][0].x_)
	{
		cout << "NO" << endl;
		return 0;
	}
	//make h1 the lower horizontal, h2 the higher
	if (p[h1][0].y_ > p[h2][0].y_)
		swap(h1, h2);
	//make v1 the left vertical, v2 the right
	if (p[v1][0].x_ > p[v2][0].x_)
		swap(v1, v2);
	//if the four points marked and sorted by h1 h2 are exactly the points marked and sorted by v1 v2, YES
	if (p[h1][0] == p[v1][0] && p[h1][1] == p[v2][0] && p[h2][0] == p[v1][1] && p[h2][1] == p[v2][1])
		cout << "YES" << endl;
	else cout << "NO" << endl;
	return 0;
}
