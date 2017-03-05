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
	ExSaver RersSaver;//contain of receivers
	ExSaver TersSaver;//contain of transimiters
	//typedef vector<Exchange_Item>::iterator ItemItertype;
	string Rers_file = "receiver" + suffix + ".csv";
	string Ters_file	= "transimitter" + suffix + ".csv";

	readCSVdata(Rers, Rers_file,1);// initiation
	readCSVdata(Ters, Ters_file,1);
	size_t a = dealRepetition(Rers, Ters);//除了为Res_money==0的元素不再有Rers和Ters中不再有Res相等的了。
	
	Rers.sort(compItemNoMaxWeight);
	Ters.sort(compItemNoMaxWeight);
	Itertype iterR = Rers.begin();
	while ((*iterR).getResMoney()==0)
	{
		RersSaver.push_back(*iterR);
		Rers.pop_front();
		iterR = Rers.begin();
	}
	Itertype iterT = Ters.begin();
	while ((*iterT).getResMoney() == 0)
	{
		TersSaver.push_back(*iterT);
		Ters.pop_front();
		iterT = Ters.begin();
	}

	while (Rers.size() && Ters.size())
	{
		if (Ters.back().getResMoney() > Rers.back().getResMoney())
		{
			exchangeFunc(Ters, Rers, TersSaver, RersSaver);
		}
		else
			exchangeFunc(Rers, Ters, RersSaver, TersSaver);
		if (RersSaver.size() % 1000 == 0)
			cout << "Rp0_num/Rers_size:\t" << RersSaver.size() << "/" << Rers.size() << endl;
	}
	//sort(RersSaver.begin(), RersSaver.end(), compOrder);
	//sort(TersSaver.begin(), TersSaver.end(), compOrder);
	RersSaver.sort(compOrder);
	TersSaver.sort(compOrder);
	clock_t finish = clock();
	string result_log = "log_" + suffix + ".txt";
	double t = double(finish - start) / CLOCKS_PER_SEC;
	writeLog(result_log, RersSaver, TersSaver, t);
	cout << t << " (s) " << endl;
	cout << "Sum of exchange times:\t"<<sumExTimes(RersSaver) << endl;
	cout << "Maxium exchange times of Rers:\t" << (*maxExTimes(RersSaver)).getWeight() << endl;
	cout << "Maxium exchange times of Ters:\t" << (*maxExTimes(TersSaver)).getWeight() << endl;
	string Rresult_file = "R_result_mixed2_" + suffix + ".csv";
	string Tresult_file = "T_result_mixed2_" + suffix + ".csv";
	writeResult(RersSaver, Rresult_file);
	writeResult(TersSaver, Tresult_file);
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