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
	cout << "Please enter the label of the file:";
	string suffix;
	cin >> suffix;
	clock_t start = clock();
	vector<Exchange_Item> Rer;//contain of receivers
	vector<Exchange_Item> Ter;//contain of transimiters
	//typedef vector<Exchange_Item>::iterator ItemItertype;
	string Rer_file = "receiver" + suffix + ".csv";
	string Ter_file	= "transimitter" + suffix + ".csv";

	readCSVdata(Rer, Rer_file,1);// initiation
	readCSVdata(Ter, Ter_file,1);
	int a = 1;
	a = dealRepetition(Rer, Ter);//除了为Res_money==0的元素不再有Rer和Ter中不再有Res相等的了。
	
	sort(Rer.begin(), Rer.end(), compItemNoMaxWeight);
	sort(Ter.begin(), Ter.end(), compItemNoMaxWeight);
	a = distance(Rer.begin(), Rer.end());
	// the first Item whose res_money >0 
	difftype Rp0_num = finishedNum(Rer);
	//Rer.begin()+Rp0_num ponited the first nonezeroItem
	difftype Tp0_num = finishedNum(Ter);

	Itertype it1, it2;
	Exchange_Item tmp, tmp1, tmp2;
	difftype dist1(0), dist2(0);
	while (Rp0_num<Rer.size() && Tp0_num < Ter.size())
	{
		if (Ter.back().getResMoney() > Rer.back().getResMoney())
		{
			exchangeFun(Ter, Rer, Rp0_num, Tp0_num);
		}
		else
			exchangeFun(Rer, Ter, Tp0_num, Rp0_num);
	}
	sort(Rer.begin(), Rer.end(), compOrder);
	sort(Ter.begin(), Ter.end(), compOrder);

	clock_t finish = clock();

	string result_log = "log_" + suffix + ".txt";
	double t = double(finish - start) / CLOCKS_PER_SEC;
	writeLog(result_log, Rer, Ter, t);
	cout << t << " (s) " << endl;
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
