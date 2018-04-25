#include <iostream>
#include <set>
#include <array>
using namespace std;
struct envlp
{
	int width;
	int height;
	int number;
};
int envlp_num, card_h, card_w;
set<array<int, 3>> qualified_envlp;
envlp *qualified_seq;
int *num, *max_size, len;

void init()
{
	len = qualified_envlp.size();
	qualified_seq = new envlp[len];
	auto i = 0;
	for (auto x : qualified_envlp)
	{
		envlp new_envlp{ x[0],x[1],x[2] };
		qualified_seq[i] = new_envlp;
		++i;
	}
	num = new int[len];
	max_size = new int[len];
	for (i = 0; i < len; ++i)
	{
		num[i] = -1; max_size[i] = 1;
	}
	num[0] = -2;
}


void n_end(int n)
{
	if (n <= 0)
		return;
	int height_n{ qualified_seq[n].height }, width_n{ qualified_seq[n].width };
	set<int> low;
	int msize{ 0 }, max_i{ n };
	for (auto i = 0; i < n; ++i)
	{
		if(num[i] == -1)
			n_end(i);
		int msize_i = max_size[i];
		if (qualified_seq[i].height < height_n && qualified_seq[i].width < width_n)
		{
			if (msize < msize_i)
			{
				msize = msize_i;
				max_i = i;
			}
		}
	}
	num[n] = max_i;
	max_size[n] = msize + 1;
}

int main()
{

	cin >> envlp_num >> card_h >> card_w;
	int envlp_h, envlp_w;
	for (auto i = 1; i <= envlp_num; ++i)
	{
		cin >> envlp_h >> envlp_w;
		if (card_h < envlp_h&&card_w < envlp_w)
			qualified_envlp.insert({ envlp_h, envlp_w, i });
	}
	if (qualified_envlp.empty())
	{
		cout << 0 << endl; return 0;
	}
	init();
	n_end(len - 1);
	int rslt_max{ -1 }, rslt_pos;
	for (auto i = 0; i < len; ++i)
	{
		if (rslt_max < max_size[i])
		{
			rslt_max = max_size[i];
			rslt_pos = i;
		}
	}
	cout << rslt_max << endl;
	int *rslt_chain = new int[rslt_max];
	for (int i = rslt_pos, j = 0; j < rslt_max; i = num[i])
	{
		rslt_chain[rslt_max - j - 1] = qualified_seq[i].number;
		++j;
	}
	for (auto i = 0; i < rslt_max; ++i)
		cout << rslt_chain[i] << " ";
	cout << endl;
	return 0;
}





