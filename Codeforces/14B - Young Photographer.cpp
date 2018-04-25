#include<iostream>
#include<algorithm>
using namespace std;

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);

	int num_segments, current_pos;
	cin >> num_segments >> current_pos;
	int best_startpos{ 0 }, best_endpos{ 1001 };
	int startpos, endpos;
	for (int i = 0; i < num_segments; ++i)
	{
		cin >> startpos >> endpos;
		if (startpos > endpos)
			swap(startpos, endpos);
		if (endpos<best_startpos || startpos>best_endpos)
		{
			cout << -1 << endl;
			return 0;
		}
		best_startpos = max(best_startpos, startpos);
		best_endpos = min(best_endpos, endpos);
	}
	int least_moves;
	if (current_pos < best_startpos)
		least_moves = best_startpos - current_pos;
	else if (current_pos > best_endpos)
		least_moves = current_pos - best_endpos;
	else least_moves = 0;
	cout << least_moves << endl;
	return 0;
}
