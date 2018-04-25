#include <vector>
#include <iterator>
using namespace std;
float* InsertionSort(float *a, int len)
{
	int i,j;
	for (i=1;i<len;i++)
	{
		float a_i=a[i];
		j=i;
		while(a[j-1]>a_i && j>=1)
		{
			a[j]=a[j-1];
			j--;
		}
		a[j]=a_i;
	}
    return a;
}


/*void insertion_sort(vector<float> &vct_flt0)
{
	auto itr0=vct_flt0.begin();
	vector<float>::iterator itr1,itr2;
	float key;
	for (itr0++;itr0!=vct_flt0.end();itr0++)
	{
		key=*itr0;
		itr1=itr0-1;
		while(*itr1>key && itr1>=vct_flt0.begin())
		{
			itr2=itr1+1;
			*itr2=*itr1;
			itr1--;
		}
		itr2=itr1+1;
		*itr2=key;
	}
}*/





