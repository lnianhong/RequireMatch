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
	cout << "Please enter the lable of the file:";
	string suffix;
	cin >> suffix;
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

	ExContainer::size_type Rers_size = Rers.size();
	ExContainer::size_type Ters_size = Ters.size();

	while (Rp0_num<Rers_size && Tp0_num < Ters_size)
	{
		if (Ters.back().getResMoney() > Rers.back().getResMoney())
		{
			exchangeFunc(Ters, Rers, Rp0_num, Tp0_num);
		}
		else
			exchangeFunc(Rers, Ters, Tp0_num, Rp0_num);
		if (Rp0_num % 1000 == 0)
			cout << "Rp0_num/Rers_size:\t" << Rp0_num << "/" << Rers_size << endl;
	}
	Rers.sort(compOrder);
	Ters.sort(compOrder);
	clock_t finish = clock();
	string result_log = "log_" + suffix + ".txt";
	double t = double(finish - start) / CLOCKS_PER_SEC;
	writeLog(result_log, Rers, Ters, t);
	cout << t << " (s) " << endl;
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


