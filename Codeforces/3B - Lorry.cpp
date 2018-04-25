//404ms
#include <iostream>
using namespace std;

void boat_swap(long **boats, long i, long j)
{
	long val = boats[i][0];
	boats[i][0] = boats[j][0];
	boats[j][0] = val;
	val = boats[i][1];
	boats[i][1] = boats[j][1];
	boats[j][1] = val;
}

//insertion sort causes time excced
void boat_quick_sort(long **boats, long left, long right)
{
	if (right - left <= 0)
		return;
	else
	{
		long centor = (left + right) / 2;
		if (boats[left][0] < boats[right][0])
			boat_swap(boats, left, right);
		if (boats[left][0] < boats[centor][0])
			boat_swap(boats, left, centor);
		if (boats[centor][0] < boats[right][0])
			boat_swap(boats, right, centor);
		if (right - left <= 1)
			return;
		boat_swap(boats, centor, right - 1);
		long pivot = boats[right - 1][0];
		long i = left, j = right - 1;
		while (true)
		{
			while (boats[++i][0] > pivot) {}
			while (boats[--j][0] < pivot) {}
			if (i < j)
				boat_swap(boats, i, j);
			else break;
		}
		boat_swap(boats, i, right - 1);
		boat_quick_sort(boats, left, i - 1);
		boat_quick_sort(boats, i + 1, right);
	}
}

int main()
{
	long boat_num, truck_vol;
	cin >> boat_num >> truck_vol;
	long **type1 = new long*[boat_num], **type2 = new long*[boat_num];
	long num1{ 0 }, num2{ 0 };
	for (auto i = 1; i <= boat_num; ++i)
	{
		long typ, val;
		cin >> typ >> val;
		if (typ == 1)
		{
			type1[num1] = new long[2];
			type1[num1][0] = val;
			type1[num1][1] = i;
			++num1;
		}
		else
		{
			type2[num2] = new long[2];
			type2[num2][0] = val;
			type2[num2][1] = i;
			++num2;
		}
	}
	boat_quick_sort(type1, 0, num1 - 1);
	boat_quick_sort(type2, 0, num2 - 1);
	
	long long total_val{ 0 };
	long *loaded_seq = new long[boat_num], seq_num{ 0 };
	long cnt1{ 0 }, cnt2{ 0 };
	if (truck_vol % 2 != 0)
	{
		if (num1 > 0)
		{
			total_val = total_val + type1[cnt1][0];
			loaded_seq[seq_num] = type1[cnt1][1];
			--truck_vol; ++cnt1; ++seq_num;
		}
		else if (truck_vol == 1)
		{
			cout << 0 << endl << endl; return 0;
		}
	}
	while (truck_vol > 0 && (cnt1 < num1 || cnt2 < num2))
	{
		long val1{ 0 };
		for (auto i = cnt1; i < num1 && i - cnt1 < 2; ++i)
			val1 = val1 + type1[i][0];
		long val2 = cnt2 < num2 ? type2[cnt2][0] : 0;
		if (val1 > val2)
		{
			total_val = total_val + val1;
			for (auto i=0; cnt1 < num1 && i < 2; ++i)
			{
				loaded_seq[seq_num] = type1[cnt1][1];
				--truck_vol; ++seq_num; ++cnt1;
			}
		}
		else
		{
			total_val = total_val + val2;
			loaded_seq[seq_num] = type2[cnt2][1];
			truck_vol = truck_vol - 2; ++seq_num; ++cnt2;
		}
	}
	cout << total_val << endl;
	for (auto i=0;i<seq_num;++i)
		cout << loaded_seq[i] << " ";
	cout << endl;
	return 0;
}

//436ms
/*
#include <iostream>
#include <set>
#include <array>
using namespace std;

int main()
{
	long boat_num, truck_vol;
	cin >> boat_num >> truck_vol;
	set<array<long, 2>> type1, type2;
	long typ, val;
	for (long cnt = 1; cnt <= boat_num; ++cnt)
	{
		cin >> typ >> val;
		if (typ == 1)
			type1.insert({ val,cnt });
		else type2.insert({ val,cnt });
	}

	long long total_val{ 0 };
	long *loaded_seq = new long[boat_num], seq_num{ 0 };
	auto ritr1 = type1.rbegin(), ritr2 = type2.rbegin();
	auto ritr1_next = type1.empty() ? type1.rend() : ++type1.rbegin();
	if (truck_vol % 2 != 0)
	{
		if (!type1.empty())
		{
			total_val = total_val + (*ritr1)[0];
			loaded_seq[seq_num]=((*ritr1)[1]);
			++seq_num;
			--truck_vol;
			++ritr1;
			if (ritr1_next != type1.rend())
				++ritr1_next;
		}
		else if (truck_vol == 1)
		{
			cout << 0 << endl << endl;
			return 0;
		}
	}
	while (truck_vol > 0 && !(ritr1 == type1.rend() && ritr2 == type2.rend()))
	{
		long type1_val, type2_val;
		type1_val = ritr1_next == type1.rend() ? 0 : (*ritr1_next)[0];
		type1_val = ritr1 == type1.rend() ? type1_val : (*ritr1)[0] + type1_val;
		type2_val = ritr2 == type2.rend() ? 0 : (*ritr2)[0];
		if (type1_val >= type2_val)
		{
			total_val = total_val + type1_val;
			for (auto i = 0; i < 2 && ritr1 != type1.rend(); ++i)
			{
				--truck_vol;
				loaded_seq[seq_num] = ((*ritr1)[1]);
				++seq_num;
				++ritr1;
			}
			for (auto i = 0; i < 2 && ritr1_next != type1.rend(); ++i)
				++ritr1_next;
		}
		else
		{
			total_val = total_val + type2_val;
			loaded_seq[seq_num] = ((*ritr2)[1]);
			++seq_num;
			truck_vol = truck_vol - 2;
			++ritr2;
		}
	}
	cout << total_val << endl;
	for (auto i=0;i<seq_num;++i)
		cout << loaded_seq[i] << " ";
	cout << endl;
	return 0;
}
*/

