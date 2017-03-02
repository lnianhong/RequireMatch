#include <iostream>  
#include <vector>  
#include <bitset>  
#include "Exchange_Item.h"
#include "requirematch.h"
#include "CSVRow.h"
#include <cstdlib>
#include <algorithm>
#include <ctime> 
#include <iterator> 

using namespace std;

//int main() {
//	//{ 2,5,15,8,20 };
//	int arr[] = { 1,2,3,4,5,6,7,8,9,10,11,12,13,14,20 };
//	//int arr[] = { 0,20 };
//	vector<int> W(arr, arr + sizeof(arr) / sizeof(int));
//	vector<bool> included(sizeof(arr) / sizeof(int), false);
//	vector<bool> includedv2(sizeof(arr) / sizeof(int), false);
//	subsetSum(W, included, 0, 20, 0);//decrease order
//	cout << "*********increase order********" << endl;
//	subsetSum(W, includedv2, 20, W.size()-1);//increase order
//
//	system("pause");
//	return 0;
//}

int main() {
	clock_t start, finish;
	start = clock();
	vector<Exchange_Item> Rer;//contain of receivers
	vector<Exchange_Item> Ter;//contain of transimiters
	//typedef vector<Exchange_Item>::iterator ItemItertype;
	readCSVdata(Rer, "receiver_S.csv");
	readCSVdata(Ter, "transimiter_S.csv");
	int a = 1;
	a = dealRepetition(Rer, Ter);//除了为Res_money==0的元素不再有Rer和Ter中不再有Res相等的了。
	
	sort(Rer.begin(), Rer.end(), compItemNoMaxWeight);
	sort(Ter.begin(), Ter.end(), compItemNoMaxWeight);
	a = distance(Rer.begin(), Rer.end());
	// the first Item whose res_money >0 
	vector<Exchange_Item>::difference_type Rp0_num = finishedNum(Rer);
	//Rer.begin()+Rp0_num ponited the first nonezeroItem
	vector<Exchange_Item>::difference_type Tp0_num = finishedNum(Ter);
	cout << "*************Receiver******************" << endl;
	for (Itertype iter = Rer.begin(); iter != Rer.end(); ++iter)
	{
		(*iter).print();
	}
	cout << "*************Transimiter******************" << endl;
	for (Itertype iter = Ter.begin(); iter != Ter.end(); ++iter)
	{
		(*iter).print();
	}
	Itertype it1, it2;
	has2sum(Rer.begin()+ Rp0_num, Rer.end(),Ter.back(),it1,it2);
	finish = clock();
	cout << double(finish - start)/ CLOCKS_PER_SEC << " (s) " << endl;
	system("pause");
	return 0;
}
