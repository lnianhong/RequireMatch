#include <iostream>  
#include <vector>  
#include <bitset>  
#include "Exchange_Item.h"
#include "requirematch.h"
#include "CSVRow.h"
#include <cstdlib>
#include <algorithm>

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
bool comp( Exchange_Item& Item1, Exchange_Item& Item2)
{
	return true;
}

int main() {
	//int arr[] = { 2,5,15,8,20 };
	//vector<int> v(arr, arr + sizeof(arr) / sizeof(int));
	//vector<bool> included(sizeof(arr) / sizeof(int), false);

	vector<int> W = { 2, 4, 6, 8, 10 };
	bitset<5> X;
	subsetsum(W, X, 0, 20, 0);
	vector<Exchange_Item> Receiver;
	std::ifstream	file("receiver_S.csv");
	typedef vector<Exchange_Item>::iterator ItemItertype;
	CSVRow	row;
	while (file >> row)
	{
		Exchange_Item tmp(row[0],atoi(row[1].c_str()));
		Receiver.push_back(Exchange_Item(row[0], atoi(row[1].c_str())));
		tmp.print();
	}
	sort(Receiver.begin(), Receiver.end(), comp);
	for (ItemItertype iter = Receiver.begin(); iter != Receiver.end(); ++iter)
	{
		(*iter).print();
	}
	system("pause");
	return 0;
}
