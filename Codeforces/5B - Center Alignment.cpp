#include <iostream>
#include <string>
using namespace std;

int main()
{
	string text[1001];
	int line_len[1000];
	int text_len{ 0 } , text_width{ -1 };
	string in_str;
	for (; text_len < 1000 && getline(cin, text[text_len]); ++text_len)
	{
		line_len[text_len] = text[text_len].size();
		if (text_width < line_len[text_len])
			text_width = line_len[text_len];
	}

	string full_star, full_space;
	full_star.resize(text_width, '*');
	full_space.resize(text_width, ' ');

	bool left{ true }, width_even{ text_width % 2 == 0 };
	string left_pad, right_pad;
	for (auto i = 0; i < text_len; ++i)
	{
		int len = line_len[i];
		if (len > 0)
		{
			bool line_even = len % 2 == 0;
			int start_pos;
			if (line_even == width_even)
				start_pos = int(text_width / 2) - int(len / 2);
			else if (left)
			{
				start_pos = int((text_width - 1) / 2) - int(len / 2);
				left = false;
			}
			else
			{
				start_pos = int((text_width - 1) / 2) - int(len / 2) + 1;
				left = true;
			}
			left_pad.resize(start_pos, ' ');
			right_pad.resize(text_width - start_pos - len, ' ');
			text[i] = left_pad + text[i] + right_pad;
		}
		else text[i] = full_space;
	}

	cout << '*' << full_star << '*' << endl;
	for (auto i = 0; i < text_len; ++i)
		cout << '*' << text[i] << '*' << endl;
	cout << '*' << full_star << '*' << endl;
	return 0;
}