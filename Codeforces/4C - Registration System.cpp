#include <iostream>
#include <vector>
#include <string>
using namespace std;

struct name
{
	string str;
	int num{ 0 };
};
int main()
{
	int n;
	cin >> n;
	vector<name> database[33];
	string str;
	for (auto i = 0; i < n; ++i)
	{
		cin >> str;
		int len = str.size();
		bool found{ false };
		for (auto itr= database[len].begin(); itr!= database[len].end(); ++itr)
		{
			if (itr->str == str)
			{
				cout << str << ++(itr->num) << endl;
				found = true;
				break;
			}
		}
		if (!found)
		{
			name new_name;
			new_name.str = str;
			database[len].push_back(new_name);
			cout << "OK" << endl;
		}
	}
	return 0;
}




//#include <iostream>
//#include <map>
//#include <string>
//using namespace std;
//
//int main()
//{
//	int n;
//	cin >> n;
//	map<string,int> database;
//	string str;
//	for (auto i = 0; i < n; ++i)
//	{
//		cin >> str;
//		auto itr = database.find(str);
//		if (itr != database.end())
//		{
//			++(itr->second);
//			cout << str << itr->second << endl;
//		}
//		else
//		{
//			database[str] = 0;
//			cout << "OK" << endl;
//		}
//	}
//	return 0;
//}

