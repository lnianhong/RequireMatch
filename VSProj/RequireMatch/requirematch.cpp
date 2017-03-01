#include "requirematch.h"
#include "Exchange_Item.h"
#include "CSVRow.h"
#include <iostream>  
#include <vector>  
#include <bitset>  
//using namespace std;
/******************************************************************/
// compare the priority level of the Items; 
bool compItemNoMaxWeight(const Exchange_Item& Item1, const Exchange_Item& Item2)
{
	if (Item1.getResMoney() < Item2.getResMoney())
		return true;
	else if (Item1.getResMoney() > Item2.getResMoney())
		return false;
	else
		//return true;
		return Item1.getID() < Item2.getID();
}

bool compItem(const Exchange_Item& Item1, const Exchange_Item& Item2)
{
	if (Item1.getWeight() >= (Item1.maxWeight() - 1)) //Item1 已达到最大次数
	{
		if (Item2.getWeight() > Item1.getWeight()) // Item2 已达到最大次数且超越Item1
			return true;
		else //Item2.getWeight() <= Item1.getWeight()
		{
			if (Item2.getWeight() == Item1.getWeight()) 
				return compItemNoMaxWeight(Item1,Item2);// Item2 未达到最大次数
			else 
				return false;		
		}
	}
	else//Item1 未达到最大次数
	{	
		if (Item2.getWeight() >= (Item2.maxWeight() - 1)) // Item2 已达到最大次数
			return true;
		else
			return compItemNoMaxWeight(Item1, Item2);
	}
}
/*read csv data*/
bool readCSVdata(std::vector<Exchange_Item>& Rer, const std::string csvfilename)
{
	std::ifstream Rfile(csvfilename);
	CSVRow	Rrow;
	while (Rrow.readNextRow(Rfile))
	{
		//Exchange_Item tmp(row[0], atoi(row[1].c_str()));
		Rer.push_back(Exchange_Item(Rrow[0], atoi(Rrow[1].c_str())));
	}
	Rfile.close();
	return true;
}
/******************************************************************/
// 子集和问题
//void print(const vector<int> & w, const bitset<5> & x)
//{
//	cout << "{";
//	for (unsigned int i = 0; i < x.size(); ++i)
//	{
//		if (x[i])
//		{
//			cout << w[i] << " ";
//		}
//	}
//	cout << "}";
//	cout << endl;
//}
//bool subsetsum(const vector<int>& w, bitset<5>& x, int sum, int targetsum, int k)
//{
//	x[k] = 1; // try one branch of tree  
//	if (sum + w[k] == targetsum)
//		print(w, x); // we have a solution  
//	else
//	{
//		if (k + 1 < w.size() && sum + w[k] <= targetsum) // include the w[k]
//			subsetsum(w, x, sum + w[k], targetsum, k + 1); // the maxium k is w.size-2
//		if (k + 1 < w.size() && sum + w[k + 1] <= targetsum)
//		{
//			x[k] = 0; // uniclude the w[k]
//			subsetsum(w, x, sum, targetsum, k + 1); // the maxium k is w.size-2
//		}
//	}
//	return true;
//
//}