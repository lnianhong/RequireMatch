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
	string suffix("S");
	clock_t start = clock();
	vector<Exchange_Item> Rer;//contain of receivers
	vector<Exchange_Item> Ter;//contain of transimiters
	//typedef vector<Exchange_Item>::iterator ItemItertype;
	string Rer_file = "receiver_" + suffix + ".csv";
	string Ter_file	= "transimiter_" + suffix + ".csv";
	readCSVdata(Rer, Rer_file);// initiation
	readCSVdata(Ter, Ter_file);
	int a = 1;
	a = dealRepetition(Rer, Ter);//除了为Res_money==0的元素不再有Rer和Ter中不再有Res相等的了。
	
	sort(Rer.begin(), Rer.end(), compItemNoMaxWeight);
	sort(Ter.begin(), Ter.end(), compItemNoMaxWeight);
	a = distance(Rer.begin(), Rer.end());
	// the first Item whose res_money >0 
	vector<Exchange_Item>::difference_type Rp0_num = finishedNum(Rer);
	//Rer.begin()+Rp0_num ponited the first nonezeroItem
	vector<Exchange_Item>::difference_type Tp0_num = finishedNum(Ter);

	Itertype it1, it2;
	Exchange_Item tmp, tmp1, tmp2;
	vector<Exchange_Item>::difference_type dist1(0), dist2(0);
	while (Rp0_num<Rer.size() && Tp0_num < Ter.size())
	{
		if (Ter.back().getResMoney() > Rer.back().getResMoney())
		{
			//if (has2sum(Rer.begin() + Rp0_num, Rer.end(), Ter.back(), it1, it2))//it1 is in the front of it2
			//{
			//	//set the exchange info
			//	Ter.back().addExchangeInfo((*it1).getID(), (*it1).getResMoney());
			//	Ter.back().addExchangeInfo((*it2).getID(), (*it2).getResMoney());
			//	Ter.back().weightIncrease(2);
			//	Ter.back().setResMoney(0);
			//	tmp = Ter.back();
			//	(*it1).addExchangeInfo(tmp.getID(), (*it1).getResMoney());
			//	(*it1).weightIncrease();
			//	(*it1).setResMoney(0);
			//	(*it2).addExchangeInfo(tmp.getID(), (*it2).getResMoney());
			//	(*it2).weightIncrease();
			//	(*it2).setResMoney(0);
			//	tmp1 = (*it1);
			//	tmp2 = (*it2);
			//	dist1 = distance(Rer.begin(), it1);
			//	dist2 = distance(Rer.begin(), it2);
			//	//change the Ters 
			//	Ter.pop_back();
			//	Ter.insert(Ter.begin() + Tp0_num, tmp);
			//	Tp0_num++;
			//	//change the Rers 
			//	Rer.erase(Rer.begin() + dist2);
			//	Rer.erase(Rer.begin() + dist1);
			//	Rer.insert(Rer.begin() + Rp0_num, tmp2);
			//	Rp0_num++;
			//	Rer.insert(Rer.begin() + Rp0_num, tmp1);
			//	Rp0_num++;
			//}
			//else //处理2个Item，一个为0，一个减小并插入（另一列中不会有相等的数）
			//{
			//	Ter.back().addExchangeInfo(Rer.back().getID(), Rer.back().getResMoney());
			//	Ter.back().weightIncrease();
			//	Ter.back().setResMoney(Ter.back().getResMoney() - Rer.back().getResMoney());

			//	Rer.back().addExchangeInfo(Ter.back().getID(), Rer.back().getResMoney());
			//	Rer.back().weightIncrease();
			//	Rer.back().setResMoney(0);
			//	//change the Ter 
			//	tmp = Ter.back();
			//	Ter.pop_back();
			//	// 插在第一个大于等于的值的前面
			//	Itertype iter_insert = lower_bound(Ter.begin() + Tp0_num, Ter.end(), tmp, compItem);
			//	Ter.insert(iter_insert, tmp);
			//	//change the Rer
			//	tmp1 = Rer.back();
			//	Rer.pop_back();
			//	Rer.insert(Rer.begin() + Rp0_num, tmp1);
			//	Rp0_num++;
			//}
			exchangeFun(Ter, Rer, Rp0_num, Tp0_num);

		}
		else
			exchangeFun(Rer, Ter, Tp0_num, Rp0_num);
	}
	sort(Rer.begin(), Rer.end(), compID);
	sort(Ter.begin(), Ter.end(), compID);
	//has2sum(Rer.begin()+ Rp0_num, Rer.end(),Ter.back(),it1,it2);
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



	clock_t finish = clock();
	cout << double(finish - start)/ CLOCKS_PER_SEC << " (s) " << endl;
	cout << "Sum of exchange times:\t"<<sumExTimes(Rer) << endl;
	cout << "Maxium exchange times of Rer:\t" << (*maxExTimes(Rer)).getWeight() << endl;
	cout << "Maxium exchange times of Ter:\t" << (*maxExTimes(Ter)).getWeight() << endl;
	string Rresult_file = "R_result_" + suffix + ".csv";
	string Tresult_file = "T_result_" + suffix + ".csv";
	writeResult(Rer, Rresult_file);
	writeResult(Ter, Tresult_file);
	system("pause");
	return 0;
}
