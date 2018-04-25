#pragma once
#include <iostream>
#include <vector>
using namespace std;
vector<double> MidCrossing(vector<double> &vct, size_t st, size_t mid, size_t ed)
{
	double sum{ 0 }, sum_l{ -DBL_MAX }, sum_h{ -DBL_MAX };
	size_t l, h;
	for (int i = mid; i >= int(st); --i)//avoid default conversion: int -> unsigned int
	{
		sum += vct[i];
		if (sum > sum_l)
		{
			sum_l = sum;
			l = i;
		}
	}
	sum = 0;
	for (int i = mid; i <= int(ed); ++i)
	{
		sum += vct[i];
		if (sum > sum_h)
		{
			sum_h = sum;
			h = i;
		}
	}
	return{ sum_l + sum_h - vct[mid], double(l), double(h) };
}


//devide and conque: n*log(n)
vector<double> MaxSubarr0(vector<double> &vct,size_t st,size_t ed)
{

	if (ed == st)
		return{ vct[st],double(st),double(ed) };
	else
	{
		vector<double> rslt_l{ 0 }, rslt_m{ 0 }, rslt_h{ 0 };
		size_t mid = (ed - st) / 2 + st;
		rslt_l = MaxSubarr0(vct, st, mid);
		rslt_h = MaxSubarr0(vct, mid+1, ed);
		rslt_m = MidCrossing(vct, st, mid,ed);
		if ((rslt_l[0] > rslt_m[0]) || (rslt_h[0] > rslt_m[0]))
			return rslt_l[0] > rslt_h[0] ? rslt_l : rslt_h;
		else return rslt_m;
	}
}


//brute-force: n^2
vector<double> MaxSubarr1(vector<double> &vct, size_t st, size_t ed)
{
	double sum{ 0 }, sum_last{ -DBL_MAX };
	size_t lo{ st }, hi{ st };
	for (size_t i = st; i <= ed; ++i)
	{
		sum = 0;
		lo = i;
		for (size_t j = i; j <= st; ++j)
		{
			sum += vct[j];
			if (sum > sum_last)
			{
				sum_last = sum;
				hi = j;
			}
		}
	}
	return{ sum_last,double(lo),double(hi) };
}



//linear
vector<double> MaxSubarr2(vector<double> &vct, size_t st, size_t ed)
{
	double sum_rgt{ 0 }, sum_last{ -DBL_MAX }, max_sum_rgt{ 0 };
	size_t lo{ st }, hi{ st }, rgt{ st };
	for (size_t i = st; i <= ed; ++i)
	{
		sum_rgt += vct[i];
		if (max_sum_rgt < 0)
		{
			max_sum_rgt = vct[i];
			rgt = i;
		}
		else max_sum_rgt += vct[i];

		if (sum_rgt > 0 && sum_rgt + sum_last > max_sum_rgt)
		{
			sum_last += sum_rgt;
			hi = i;
			sum_rgt = 0; max_sum_rgt = 0; ++rgt;
		}
		else if (max_sum_rgt > sum_last && max_sum_rgt > sum_rgt + sum_last)
		{
			sum_last = max_sum_rgt;
			lo = rgt; hi = i;
			sum_rgt = 0; max_sum_rgt = 0; ++rgt;
		}
	}
	return{ sum_last,double(lo),double(hi) };
}