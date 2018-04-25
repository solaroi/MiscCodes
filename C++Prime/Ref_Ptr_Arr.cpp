//============================================================================
// Name        : test.cpp
// Author      : Solaroi
// Version     :
// Copyright   : Your copyright notice
// Description : learning C++
//============================================================================

#include <iostream>
#include "InsertSort.h"
#include <string>
#include <cstring>
#include <vector>
#include <iterator>
using namespace std;//or "using std::string"

//extern declaration£¬indicating compiler to find the definition in other files
extern int ExtGlb0;
extern const int ExtGlb1;

int GLB0 ,GLB1=11;

void fun1(int **a)
{
	*a=&GLB0;
}

void fun2(int *(&a))
{
	a=&GLB1;
}

int main() {

	//*********************************************************************************************
	//redefine in loop
	/* vector<int> v;
	for (auto i = 0; i < 10; ++i)
	{
		int j=i;
		v.push_back(j);
		cout << &j << " ";//all j have the same addr
	}
	cout << endl;
	for (auto &i : v)
		cout << &i << " "; */
	//*********************************************************************************************
	//*********************************************************************************************
    //cout << GLB0 << " " << GLB1 << endl;//GLB0 is default initialized
	//int itg0 = 1, itg1; //itg1 is default initialized in main(), thus has undefined value
	//int  itg2{};//{} -> value initialized -> default initialized -> undefined value
	//int &rf0=itg0;//y is a reference of itg0
	//int *pt2=&rf0;//any operations to rf0 actually happened to itg0
	//int *pt0=&itg0;//equals to int *pt0;pt0=&itg0;
	//int **pt1=&pt0;//equals to int **pt1;pt1=&pt0; {int *pt1=&pt0} is invalid because pt1
	//		   //is declared to be a pointer(address) pointing to an integer
	//		   //while &pt0 is not a pointer of such type
	//cout<<pt2<<" "<<*pt2<<" "<<rf0<<endl;
	//cout<<pt0<<" "<<*pt0<<" "<<&pt0<<" "<<\
	//	  pt1<<" "<<*pt1<<" "<<**pt1<<" "<<&pt1<<endl;
	////pt0->itg0, &pt0->pt0;pt1->*pt1,*pt1->**pt1; pt1=&pt0 leads to: *pt1=pt0, **pt1=itg0
	////&(&pt0) is invalid because &pt0 is not lvalue

	////define a function to modify the variant p outside of it:
	////1. use *p as argument 2. reference of p
	////define a function to modify the value of a pointer outside of it:
	////1. use **p as argument 2. reference of the pointer
	//cout<<pt0<<" "<<*pt0<<endl;
	//fun1(&pt0); cout<<pt0<<" "<<*pt0<<endl;
	//fun2(pt0);  cout<<pt0<<" "<<*pt0<<endl;
	//cout<<ExtGlb0<<" "<<ExtGlb1<<endl;
	//**************************************************************************************************

	//**************************************************************************************************
	//string str0,str1,str2;
	//cout<<"please enter 3 strings"<<endl;
	//cin>>str0>>str1;//cin ignores the " " or \n in the front, to the next " "or \n
	//getline(cin,str2);//getline() reads from the cursor to \n
	//string str3=str0+str1+str2;
	//cout<<str3<<" "<<str3.size()<<endl;

	//for (auto &chr0 : str3)//chr0 is a reference of a char in str3
	//{
	//	if(!isspace(chr0))
	//		chr0=tolower(chr0);
	//}
	//cout<<str3<<endl;
	//for(decltype(str3.size()) idx0=0;\
	//		idx0<str3.size(); idx0++)
	//{
	//	if(!isspace(str3[idx0]))
	//		str3[idx0]=toupper(str3[idx0]);
	//}
	//cout<<str3<<endl;

	//const string str4 = "Keep out!";
	//for (auto &chr0 : str4) { cout<<chr0;}cout<<endl;

	//vector<string> vct_str0;
	//string str5;
	//cout<<"enter several strings separated by whitespace, end with \"$\""<<endl;
	//while((cin>>str5)&&(str5!="$"))
	//	vct_str0.push_back(str5);
	//cout<<vct_str0.size()<<endl;
	//vector<string> vct_str1(vct_str0.size()," received;");
	//vector<string> vct_str2(vct_str0.size());
	//for(auto str_idx:vct_str0)
	//	cout<<str_idx<<" ";
	//cout<<endl;
	//typedef vector<string>::size_type vct_str_size;
	//for(vct_str_size idx0=0; idx0<vct_str0.size(); idx0++)
	//{
	//	vct_str2[idx0]=vct_str0[idx0]+vct_str1[idx0];
	//	cout<<vct_str2[idx0]<<" ";
	//}
	//cout<<endl;
	//**********************************************************************************************

	//**********************************************************************************************
	//vector<float> vct_flt0;
	//float flt0;
	//cout<<"enter several floats separated by whitespace, end with \"-1\""<<endl;
	//while(cin>>flt0)
	//	vct_flt0.push_back(flt0);
	//for(auto vct_itr0=vct_flt0.begin();vct_itr0!=vct_flt0.end();vct_itr0++)
	//		cout<<*vct_itr0<<" ";
	//cout<<endl;
	//insertion_sort(vct_flt0);
	//for(auto vct_itr0=vct_flt0.begin();vct_itr0!=vct_flt0.end();vct_itr0++)
	//	cout<<*vct_itr0<<" ";
	//cout<<endl;
	//**********************************************************************************************

	//**********************************************************************************************
	//float arr0[]={1,2,3,4};
	//decltype(arr0) arr1={5,5,5,5};//decttype doesn't convert arr0 to &arr0[0]
	//constexpr std::size_t siz0=sizeof(arr0)/sizeof(arr0[0]);//initialization needs const expression
	//cout<<siz0<<endl;
	//auto pt0=arr0,pt1=begin(arr0);//auto transfers arr0 to &arr0[0]
	//float *pt2=arr0,*pt4=&arr0[0];
	//float *pt5=&arr0[3],*pt6=pt0+3;
	//float *pt7=&arr0[4],*pt8=end(arr0);
	//float (*pt9)[4] = &arr0;//*pt3=&arr0 is illegal, types doesn't match
	//cout<<&arr0<<" "<<pt9<<" "<< *pt9 <<endl;//&arr0 equals arr0 when cout
	//cout<<pt0<<" "<<pt1<<" "<<pt2<<" "<<pt4<<endl;
	//cout<<arr0[0]<<" "<<*pt0<<endl;
	//cout<<arr0[3]<<" "<<*(pt0+3)<<" "<<pt0[3]<<" "<<pt8[-1]<<endl;
	//float (*arr2)[siz0]=&arr1;//arr2 points to an array of 4 floats
	//for (auto flti:*arr2)
	//	cout<<flti<<" ";
	//cout<<endl;
	//float *arr3[siz0]={pt0,pt1,pt2,pt5};//arr3 points to an array of 4 float points
	//float (&arr4)[siz0]=arr0;//arr4 is an reference to an array of 4 floats
	//float (*(&arr5))[siz0]=arr2;
	//float *(&arr6)[siz0]=arr3;
	//for (auto pti=begin(arr1);pti!=end(arr1);++pti)
	//	*pti=*pti+float(pti-begin(arr1));
	//for (int itgi=0;itgi<siz0;itgi++)
	//	cout<<arr0[itgi]<<" "<<arr1[itgi]<<" "<<(*arr2)[itgi]\
	//	    <<" "<<arr3[itgi]<<" "<<arr4[itgi]<<" "<<(*arr5)[itgi]\
	//		<<" "<<arr6[itgi]<<endl;
    //**********************************************************************************************

	//**********************************************************************************************
	//char charr0[100] = "C-string\0";//null is terminator for c-string functions e.g.strcpy
	//char charr1[10] = "C-str\0ing";//when processed char by char. tips:strlen not counting null
	//cout << charr0 << " " << sizeof(charr0) / sizeof(charr0[0]) << " "  <<strlen(charr0)<< endl;
	//cout << charr1 << " " << sizeof(charr1) / sizeof(charr1[0]) << " "  <<strlen(charr1)<< endl;
	//cout << bool(charr0[46]=='\0') << endl;//all the empty position assigned to null
	////convert str0 to chrr0, str1 to chrr1
	//string str0 = "password", str1 = "received";
	////2 ways to convert str to char array
	////str0.c_str() return  pointer to null-terminated nonmutable array with content of str0
	////the array is temp, thus const: const char *chrr=str0.c_str();
	//char *chrr0 = new char[str0.length() + 1];//not default initialized to NULL
	//strcpy(chrr0, str0.c_str());
	//char *chrr1 = new char[str1.length() + 1];
	//*(chrr1 + str1.length()) = '\0';//null teminated
	//str1.copy(chrr1, str1.length(), 0);//copy 0~0+len data of str1 to chrr1,equal to the follow:
	///*for (size_t i=0;i<str1.length();i++)
	//	*(chrr1+i)=str1[i];*/
	//cout << str0.c_str() << endl;
	//cout << chrr0 << " " << sizeof(chrr0) / sizeof(chrr0[0]) << " " << strlen(chrr0) << endl;
	//cout << chrr1 << " " << sizeof(chrr1) / sizeof(chrr1[0]) << " " << strlen(chrr1) << endl;

	//char charr2[] = "usrname", *charr3 = "lost";
	//string str2 = charr2, str3 = charr3;//inicialize str with c-string: remove the null char
	//cout << sizeof(charr2) / sizeof(charr2[0]) << " " << str2.length() << endl;
	//cout << sizeof(charr3) / sizeof(charr3[0]) << " " << str3.length() <<endl;

	//char charr4[] = { 'z','w','s','y','s','u' }; char charr5[] = "1343803732";
	//str3 = charr5;//assign c-string char array to str: remove the null
	//str2 = charr4;//ordinary char array illegal, compiler goes far to find null after charr4
	//cout << str3.length() << " " << str3 << endl;
	//cout << str2.length()<<" "<<str2[5] << endl;//str.len is strange cause of far null
	//str2 = str2.substr(0, sizeof(charr4)/sizeof(charr4[0])); 
	//cout << str2 << " " << str2.length() << endl;
	//constexpr size_t siz4 = sizeof(charr4) / sizeof(charr4[0]);
	//char charr4n[siz4 + 1] = {};//all elements initialized to null
	//for (size_t i = 0; i < siz4; i++)// convert charr4 to a valid c style string, null terminated
	//	charr4n[i] = charr4[i];
	//cout << charr4n << " " << strlen(charr4n) << endl;
	//delete chrr0,chrr1;
	//**********************************************************************************************
	
	//**********************************************************************************************
	//float arr0[3][4] = { {1,2,3,4}, {5,6,7,8}, {9,10,11,12} };
	//for (size_t i = 0; i < 3; i++)
	//{
	//	for (size_t j = 0; j < 4; j++)
	//		cout << arr0[i][j] << " ";
	//	cout << endl;
	//}
	//cout << &arr0 << " " << arr0 << " " << arr0[0] << " " << &arr0[0] << " " << &arr0[0][0] << endl;
	//cout << arr0[1][1] << " " << (*(arr0 + 1))[1] << " " << *((*(arr0 + 1)) + 1) << " " << *(arr0[1] + 1) << endl;
	//cout << sizeof(arr0) << " " << sizeof(arr0[0]) << " " << sizeof(arr0)/sizeof(arr0[0]) << endl;
	////&arr0 arr0 &arr0[0] arr0[0] &arr0[0][0] 
	////pt    pt0   pt1      ref1     pt2         have the same value, but differ in type
	////pt -> arr0; pt0 -> arr0[0]=ref1; pt1=pt2 -> arr0[0][0]=ref1[0]; 
	////pt0=arr0 degrades arr0 to a pointer to arr0[0]
	////pt1=arr0[0] degrades arr0[0] to a pointer to arr0[0][0]
	//float(*pt)[3][4] = &arr0;
	//float(*pt0)[4] = arr0, *pt1 = arr0[0], *pt2 = &arr0[0][0];
	//float(*pt3)[4] = arr0 + 1, *pt4 = arr0[1], *pt5 = &arr0[1][0];
	//float(*pt6)[4] = 1+begin(arr0), *pt7 = 1+begin(*pt6);//*pt6 equals array arr0[1], not degraded
	//float(&ref0)[3][4] = arr0, (&ref1)[4] = arr0[0];
	//cout << pt0 << " " << pt1 << " " << pt2 << endl;
	//cout << pt3 << " " << pt4 << " " << pt5 << endl;
	//cout << arr0[0][0] << " " << (*pt0)[0] << " " << *pt1 << " " << *pt2 << endl;
	//cout << arr0[1][0] << " " << (*pt3)[0] << " " << *pt4 << " " << *pt5 << endl;
	//cout << pt6 << " " << pt7 << " " << **pt6 << " " << (*pt6)[1] << endl;
	//cout << ref0[1] << " " << ref1 + 1 << " " << **(&ref1 + 1) << " " << (*(&ref1 + 1))[1] << endl;
	//cout << sizeof(pt0) << " " << sizeof(*pt0) << " " << sizeof(*(pt0+1)) << endl;
	//for (auto &arr : arr0)//arr equals arr0[i] i=0,1,2
	//	for (auto flt : arr)//use ref in case arr degraded to a pointer to *arr[0]
	//		cout << flt << " ";
	//cout << endl;
	//for (auto pti = begin(arr0); pti != end(arr0); ++pti)
	//	for (auto pti1 = begin(*pti); pti1 != end(*pti); ++pti1)
	//		cout << *pti1 << " ";
	//cout << endl;
	//for (float(*pti)[4] = arr0; pti < arr0 + 3; ++pti)
	//	for (float *pti1 = *pti; pti1 < *pti + 4; pti1++)//*pti degraded to a pointer to *pti[0]
	//		cout << *pti1 << " ";
	//cout << endl;
	//**********************************************************************************************
	return 0;
}

