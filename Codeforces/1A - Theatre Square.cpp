#include <iostream>
using namespace std;
int main()
{
	unsigned long long N, M, a;
	cin >> N >> M >> a;
	auto row = N % a == 0 ? N / a : N / a + 1;
	auto col = M % a == 0 ? M / a : M / a + 1;
	cout << fixed << row*col << endl;
}