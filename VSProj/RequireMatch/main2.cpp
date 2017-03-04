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
	string suffix("part");
	clock_t start = clock();
	ExContainer Rers;//contain of receivers
	ExContainer Ters;//contain of transimiters
	//typedef vector<Exchange_Item>::iterator ItemItertype;
	string Rers_file = "receiver" + suffix + ".csv";
	string Ters_file	= "transimitter" + suffix + ".csv";

	readCSVdata(Rers, Rers_file,1);// initiation
	readCSVdata(Ters, Ters_file,1);
	size_t a = dealRepetition(Rers, Ters);//除了为Res_money==0的元素不再有Rers和Ters中不再有Res相等的了。
	
	Rers.sort(compItemNoMaxWeight);
	Ters.sort(compItemNoMaxWeight);

	// the first Item whose res_money >0 
	difftype Rp0_num = finishedNum(Rers);
	//Rers.begin()+Rp0_num ponited the first nonezeroItem
	difftype Tp0_num = finishedNum(Ters);

	//string Rresult_file = "R_result_" + suffix + ".csv";
	//string Tresult_file = "T_result_" + suffix + ".csv";
	//writeResult(Rers, Rresult_file);
	//writeResult(Ters, Tresult_file);

	while (Rp0_num<Rers.size() && Tp0_num < Ters.size())
	{
		if (Ters.back().getResMoney() > Rers.back().getResMoney())
		{
			exchangeFunc(Ters, Rers, Rp0_num, Tp0_num);
		}
		else
			exchangeFunc(Rers, Ters, Tp0_num, Rp0_num);
	}
	Rers.sort(compOrder);
	Ters.sort(compOrder);
	clock_t finish = clock();
	cout << double(finish - start)/ CLOCKS_PER_SEC << " (s) " << endl;
	cout << "Sum of exchange times:\t"<<sumExTimes(Rers) << endl;
	cout << "Maxium exchange times of Rers:\t" << (*maxExTimes(Rers)).getWeight() << endl;
	cout << "Maxium exchange times of Ters:\t" << (*maxExTimes(Ters)).getWeight() << endl;
	string Rresult_file = "R_result_list_" + suffix + ".csv";
	string Tresult_file = "T_result_list_" + suffix + ".csv";
	writeResult(Rers, Rresult_file);
	writeResult(Ters, Tresult_file);
	system("pause");
	return 0;
}


//has2sum(Rers.begin()+ Rp0_num, Rers.end(),Ters.back(),it1,it2);
//cout << "*************Receiver******************" << endl;
//for (Itertype iter = Rers.begin(); iter != Rers.end(); ++iter)
//{
//	(*iter).print();
//}
//cout << "*************Transimiter******************" << endl;
//for (Itertype iter = Ters.begin(); iter != Ters.end(); ++iter)
//{
//	(*iter).print();
//}