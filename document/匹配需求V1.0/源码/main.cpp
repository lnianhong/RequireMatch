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

int main() {
	cout << "Pleasr enter the label of the file:";
	string suffix;
	cin >> suffix;
	clock_t start = clock();
	ExContainer Rers;//contain of receivers
	ExContainer Ters;//contain of transimiters
	ExSaver RersSaver;
	ExSaver TersSaver;
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




//ExContainer Rers;//元素为收款人的容器
//ExContainer Ters;//元素为打款人的容器
//ExSaver RersSaver;//元素为完成交易的收款人的容器
//ExSaver TRersSaver;//元素为完成交易的打款人的容器
//readCSVdata(Rers, Rers_file, 1);// 从CSV入数据
//readCSVdata(Ters, Ters_file, 1);
//
//dealRepetition(Rers, Ters);//排序+对冲抵消 O（NlogN）+O(N)
//Rers.sort(compItemNoMaxWeight);//再排序，完成交易的元素余额为0，排前面 O（NlogN）
//Ters.sort(compItemNoMaxWeight);//再排序，完成交易的元素余额为0，排前面 O（NlogN）
//toSaver（Rers，RersSaver）//将完成交易的元素存入RersSaver并从Rers中删除  O(N)
//toSaver（Ters，TersSaver）
//while (Rers.size() && Ters.size())//O（N）
//{
//	if (Ters.back().getResMoney() > Rers.back().getResMoney())
//		exchangeFunc(Ters, Rers, TersSaver, RersSaver);//其中包括has2sum和交易记录,二分插入操作
//	else
//		exchangeFunc(Rers, Ters, RersSaver, TersSaver);// O(N)+O（logN）
//}
//RersSaver.sort(compOrder);//排序，按照原始顺序
//TersSaver.sort(compOrder);//排序，按照原始顺序
//writeResult(RersSaver, Rresult_file);//写结果
//writeResult(TersSaver, Tresult_file);//写结果


