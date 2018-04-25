#include <iostream>
#include <string>
#include <vector>
using namespace std;
string in_str;

vector<int> * search(int step)
{
	vector<int> *max_substr_size = new vector<int>;
	max_substr_size->push_back(-1);
	int start = step == 1 ? 0 : in_str.size() - 1;
	int end_pos = step == 1 ? in_str.size() : -1;
	char key = step == 1 ? '(' : ')';
	char in_chr;
	int cnt{ 0 }, len{ 0 };
	for (auto i = start; i != end_pos; i += step)
	{
		in_chr = in_str[i];
		if (in_chr == key)
			++cnt;
		else --cnt;
		++len;
		if (cnt < 0)
		{
			cnt = 0;
			len = 0;
			continue;
		}
		else if (cnt == 0)
		{
			if (len > max_substr_size->front())
			{
				max_substr_size->clear();
				max_substr_size->push_back(len);
			}
			else if (len == max_substr_size->front())
				max_substr_size->push_back(len);
		}
	}
	return max_substr_size;
}
int main()
{
	cin >> in_str;
	vector<int> *size_l= search(1);
	vector<int> *size_r = search(-1);
	int max_size_l = size_l->front(), max_size_r = size_r->front();
	if (max_size_l == -1 && max_size_r == -1)
		cout << 0 << ' ' << 1 << endl;
	else
	{
		int max_size = max_size_l > max_size_r ? max_size_l : max_size_r;
		int num;
		if (max_size_l == max_size_r)
			num = size_l->size() > size_r->size() ? size_l->size() : size_r->size();
		else num= max_size_l > max_size_r ? size_l->size() : size_r->size();
		cout << max_size << ' ' << num << endl;
	}
	return 0;
}