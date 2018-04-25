#include <iostream>
#include <vector>
using namespace std;

//merge V[left]~V[centor] and V[centor+1]~V[right], result stored in Temp
//finally copy them back to V
void Merge(vector<double> &V, vector<double> &Temp, int left, int centorplus1, int right)
{
	int i = left, j = centorplus1, counter=0;
	while (i < centorplus1 || j <= right)
	{
		if (i == centorplus1)
		{
			Temp[counter] = V[j]; ++j;
		}
		else if (j == right + 1)
		{
			Temp[counter] = V[i]; ++i;
		}
		else
		{
			if (V[i] <= V[j])
			{
				Temp[counter] = V[i]; ++i;
			}
			else
			{
				Temp[counter] = V[j]; ++j;
			}
		}
		++counter;
	}
	for (i = 0; i < counter; ++i)
		V[left + i] = Temp[i];
}

//sort V[left]~V[centor] and V[centor+1]~V[right]
//merge and restore back to V
void MergeSort(vector<double> &V, vector<double> &Temp, int left, int right)
{
	if (left < right)//for only one element, do nothing
	{
		int centor = (left + right) / 2;//cnetor is always less than right for at least 1 position
		MergeSort(V, Temp, left, centor);
		MergeSort(V, Temp, centor + 1, right);
		Merge(V, Temp, left, centor + 1, right);
	}
}

void MergeSort(vector<double> &V)
{
	if (V.size() != 0)
	{
		vector<double> Temp(V.size());//in the whole recursion process, only Temp is needed as new memory
		MergeSort(V, Temp, 0, V.size() - 1);
	}
}



int main()
{
	vector<double> V{ 3,2,5,1,7,4,9,0,-2,34 };
	MergeSort(V);
	for (auto data : V)
		cout << data << " ";

	return 0;
}