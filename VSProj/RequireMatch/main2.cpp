#include <iostream>  
#include <vector>  
#include <bitset>  
#include "Exchange_Item.h"
#include "requirematch.h"
#include "CSVRow.h"
#include <cstdlib>
#include <algorithm>
#include <ctime> 

using namespace std;

void printSubsetSum(const vector<int> & w,const vector<bool>& x)
{
	cout << "{";
	for (unsigned int i = 0; i < x.size(); ++i) 
	{
		if (x[i])
		{
			cout << w[i] << " ";
		}	
	}
	cout << "}";
	cout << endl;
}
bool subsetSum(const vector<int>& w, vector<bool>& x, int sum, int targetsum, int k)
{
	x[k] = true; // try one branch of tree  
	if (sum + w[k] == targetsum)
		printSubsetSum(w,x); // we have a solution  
	else
	
		if (k + 1 < w.size() && sum + w[k] <= targetsum) // include the w[k]
			subsetSum(w, x, sum + w[k], targetsum, k + 1); // the maxium k is w.size-2
		if (k + 1 < w.size() && sum + w[k + 1] <= targetsum)
		{
			x[k] = false; // uniclude the w[k]
			subsetSum(w, x, sum, targetsum, k + 1); // the maxium k is w.size-2
		}
	
	return true;

}
//bool comp( Exchange_Item& Item1, Exchange_Item& Item2)
//{
//	return true;
//}

void print(const vector<int> & w, const bitset<5> & x)
{
	cout << "{";
	for (unsigned int i = 0; i < x.size(); ++i)
	{
		if (x[i])
		{
			cout << w[i] << " ";
		}
	}
	cout << "}";
	cout << endl;
}
bool subsetsum(const vector<int>& w, bitset<5>& x, int sum, int targetsum, int k)
{
	x[k] = 1; // try one branch of tree  
	if (sum + w[k] == targetsum)
		print(w, x); // we have a solution  
	else

		if (k + 1 < w.size() && sum + w[k] <= targetsum) // include the w[k]
			subsetsum(w, x, sum + w[k], targetsum, k + 1); // the maxium k is w.size-2
		if (k + 1 < w.size() && sum + w[k + 1] <= targetsum)
		{
			x[k] = 0; // uniclude the w[k]
			subsetsum(w, x, sum, targetsum, k + 1); // the maxium k is w.size-2
		}
	
	return true;

}

int main() {
	//{ 2,5,15,8,20 };
	int arr[] = { 2,5,15,8,20 };
	vector<int> W(arr, arr + sizeof(arr) / sizeof(int));
	vector<bool> included(sizeof(arr) / sizeof(int), false);
	subsetSum(W, included, 0, 20, 0);

	vector<int> W2 = { 2,5,15,8,20 };
	bitset<5> X;
	subsetsum(W2, X, 0, 20, 0);

	system("pause");
	return 0;
}

//int main() {
//	clock_t start, finish;
//	start = clock();
//	vector<Exchange_Item> Rer;//contain of receivers
//	vector<Exchange_Item> Ter;//contain of transimiters
//	typedef vector<Exchange_Item>::iterator ItemItertype;
//	readCSVdata(Rer, "receiver_S.csv");
//	readCSVdata(Ter, "transimiter_S.csv");
//	int a = 1;
//	a = dealRepetition(Rer, Ter);
//	
//	sort(Rer.begin(), Rer.end(), compItemNoMaxWeight);
//	sort(Ter.begin(), Ter.end(), compItemNoMaxWeight);
//	// the first Item whose res_money >0 
//	vector<Exchange_Item>::size_type Rp0_num = finishedNum(Rer);
//	//Rer.begin()+Rp0_num ponited the first nonezeroItem
//	vector<Exchange_Item>::size_type Tp0_num = finishedNum(Ter);
//	cout << "*************Receiver******************" << endl;
//	for (ItemItertype iter = Rer.begin(); iter != Rer.end(); ++iter)
//	{
//		(*iter).print();
//	}
//	cout << "*************Transimiter******************" << endl;
//	for (ItemItertype iter = Ter.begin(); iter != Ter.end(); ++iter)
//	{
//		(*iter).print();
//	}
//	finish = clock();
//	cout << double(finish - start)/ CLOCKS_PER_SEC << " (s) " << endl;
//	system("pause");
//	return 0;
//}
