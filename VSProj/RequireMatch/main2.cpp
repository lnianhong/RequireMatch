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

void print(const vector<int> & w,const bitset<5> & x)
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
		print(w,x); // we have a solution  
	else
	{
		if (k + 1 < w.size() && sum + w[k] <= targetsum) // include the w[k]
			subsetsum(w, x, sum + w[k], targetsum, k + 1); // the maxium k is w.size-2
		if (k + 1 < w.size() && sum + w[k + 1] <= targetsum)
		{
			x[k] = 0; // uniclude the w[k]
			subsetsum(w, x, sum, targetsum, k + 1); // the maxium k is w.size-2
		}
	}
	return true;

}
//bool comp( Exchange_Item& Item1, Exchange_Item& Item2)
//{
//	return true;
//}

//int main() {
//	//int arr[] = { 2,5,15,8,20 };
//	//vector<int> v(arr, arr + sizeof(arr) / sizeof(int));
//	//vector<bool> included(sizeof(arr) / sizeof(int), false);
//
//	vector<int> W = { 2, 4, 6, 8, 10 };
//	bitset<5> X;
//	subsetsum(W, X, 0, 20, 0);
//	vector<Exchange_Item> Rer;
//	std::ifstream	file("Rer.csv");
//	typedef vector<Exchange_Item>::iterator ItemItertype;
//	CSVRow	row;
//	while (file >> row)
//	{
//		Exchange_Item tmp(row[0],atoi(row[1].c_str()));
//		Rer.push_back(Exchange_Item(row[0], atoi(row[1].c_str())));
//		tmp.print();
//	}
//	sort(Rer.begin(), Rer.end(), compItemNoMaxWeight);
//	for (ItemItertype iter = Rer.begin(); iter != Rer.end(); ++iter)
//	{
//		(*iter).print();
//	}
//	system("pause");
//	return 0;
//}

int main() {
	clock_t start, finish;
	start = clock();
	vector<Exchange_Item> Rer;
	vector<Exchange_Item> Ter;
	typedef vector<Exchange_Item>::iterator ItemItertype;
	readCSVdata(Rer, "receiver_S.csv");
	readCSVdata(Ter, "transimiter_S.csv");
	sort(Rer.begin(), Rer.end(), compItemNoMaxWeight);
	sort(Ter.begin(), Ter.end(), compItemNoMaxWeight);
	vector<Exchange_Item>::size_type Rponiter(0);
	vector<Exchange_Item>::size_type Tponiter(0);

	for (ItemItertype Riter = Rer.begin()+ Rponiter; Riter != Rer.end() && Tponiter < Ter.size(); ++Riter)
	{
		if ((*Riter).getResMoney())
		{
			for (ItemItertype Titer = Ter.begin()+ Tponiter; Titer != Ter.end(); ++Titer)
			{
				if ((*Riter).getResMoney() == (*Titer).getResMoney())
				{
					(*Riter).addExchangeInfo((*Titer).getID(), (*Riter).getResMoney());
					(*Riter).setResMoney(0);
					(*Riter).weightIncrease();
						
					(*Titer).addExchangeInfo((*Riter).getID(), (*Titer).getResMoney());
					(*Titer).setResMoney(0);
					(*Titer).weightIncrease();
					Tponiter++;
					Rponiter++;
					break;
				}
				else
				{
					if ((*Riter).getResMoney() > (*Titer).getResMoney())
						Tponiter++;
					else
					{
						Rponiter++;
						break;
					}
						
				}
			}
		}
		else
			Rponiter++;
	}
	
	sort(Rer.begin(), Rer.end(), compItemNoMaxWeight);
	sort(Ter.begin(), Ter.end(), compItemNoMaxWeight);

	cout << "*************Receiver******************" << endl;
	//for (ItemItertype iter = Rer.begin(); iter != Rer.end(); ++iter)
	//{
	//	(*iter).print();
	//}
	//cout << "*************Transimiter******************" << endl;
	//for (ItemItertype iter = Ter.begin(); iter != Ter.end(); ++iter)
	//{
	//	(*iter).print();
	//}
	finish = clock();
	cout << double(finish - start)/ CLOCKS_PER_SEC << " (s) " << endl;
	system("pause");
	return 0;
}
