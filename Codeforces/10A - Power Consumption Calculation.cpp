#include<iostream>
#include<algorithm>
using namespace std;


int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);

	int num_interval, power1, power2, power3, time1, time2;
	cin >> num_interval >> power1 >> power2 >> power3 >> time1 >> time2;
	int *interval_left = new int[num_interval], *interval_right = new int[num_interval];
	for (int i = 0; i < num_interval; ++i)
		cin >> interval_left[i] >> interval_right[i];
	int sum_time{ 0 };
	for (int i = 0; i < num_interval - 1; ++i)
	{
		int left = interval_left[i];
		int right = interval_right[i];
		int next_left = interval_left[i + 1];
		int energy1 = power1*min(time1 + right - left, next_left - left);
		int energy2 = power2 * (time1 + right < next_left ? min(time2, next_left - right - time1) : 0);
		int energy3 = power3 * max(next_left - right - time1 - time2, 0);
		sum_time += energy1 + energy2 + energy3;
	}
	sum_time += power1*(interval_right[num_interval - 1] - interval_left[num_interval - 1]);
	cout << sum_time << endl;
	return 0;
}


