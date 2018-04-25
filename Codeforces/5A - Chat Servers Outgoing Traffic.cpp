#include <iostream>
#include <string>
using namespace std;

int main()
{
	string str;
	int chat_number{ 0 }, traffic{ 0 };
	while (getline(cin,str))
	{
		if (str == "")
			break;
		else if (str[0] == '+')
			++chat_number;
		else if(str[0] == '-')
			--chat_number;
		else
		{
			int message_length = str.size() - 1 - str.find(':');
			traffic = traffic + chat_number*message_length;
		}
	}
	cout << traffic << endl;
	return 0;
}





