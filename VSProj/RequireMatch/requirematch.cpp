#include "requirematch.h"
#include "Exchange_Item.h"
#include "CSVRow.h"
#include <iostream>  
#include <vector>  
#include <string>
#include <bitset>  
#include <algorithm>
#include <cstdlib>
#include <iterator> 
//using namespace std;
/******************************************************************/
// compare the priority level of the Items; 
bool compItemNoMaxWeight(const Exchange_Item& Item1, const Exchange_Item& Item2) //only the res
{
	if (Item1.getResMoney() < Item2.getResMoney())
		return true;
	else
		return false;
	//else if (Item1.getResMoney() > Item2.getResMoney())
	//	return false;
	//else
	//	//return true;
	//	return Item1.getID() < Item2.getID(); // It's useless
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

/*先排序然后通过移动“指针”的方式抵消重复的结果*/
int dealRepetition(std::vector<Exchange_Item>& Rer, std::vector<Exchange_Item>& Ter)
{
	int num_same(0);
	sort(Rer.begin(), Rer.end(), compItemNoMaxWeight);
	sort(Ter.begin(), Ter.end(), compItemNoMaxWeight);
	std::vector<Exchange_Item>::size_type Rponiter(0);
	std::vector<Exchange_Item>::size_type Tponiter(0);

	for (Itertype Riter = Rer.begin() + Rponiter; Riter != Rer.end() && Tponiter < Ter.size(); ++Riter)
	{
		if ((*Riter).getResMoney())
		{
			for (Itertype Titer = Ter.begin() + Tponiter; Titer != Ter.end(); ++Titer)
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
					num_same++;
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
	return num_same;

}
/*获取已经处理完（Res_money==0）的条目*/
std::vector<Exchange_Item>::difference_type finishedNum(std::vector<Exchange_Item>& Rer)
{
	Exchange_Item zeroItem("ZERO", 0);
	Itertype Rp = upper_bound(Rer.begin(), Rer.end(), zeroItem, compItemNoMaxWeight);
	std::vector<Exchange_Item>::difference_type Rp0_num = distance(Rer.begin(),Rp);
	return Rp0_num;
}

/******************************************************************/
//子集和问题
//twosum
bool has2sum(Itertype& first, Itertype& last, Exchange_Item& target,
			Itertype& it1,Itertype& it2)
{
	last--;
	while (first!=last)
	{ 
		if ((*first).getResMoney() + (*last).getResMoney() == target.getResMoney())
		{
			it1 = first;
			it2 = last;
			return true;
		}
		else if ((*first).getResMoney() + (*last).getResMoney() < target.getResMoney())
			first++;
		else
			last--;
	}
	return false;
}

//subsetsum
void printSubsetSum(const std::vector<int> & w, const std::vector<bool>& x)
{
	std::cout << "{";
	for (unsigned int i = 0; i < x.size(); ++i)
	{
		if (x[i])
		{
			std::cout << w[i] << " ";
		}
	}
	std::cout << "}";
	std::cout << std::endl;
}

//先返回元素多的
//decrease order
bool subsetSum(const std::vector<int>& w, std::vector<bool> x, int sum, int targetsum, int k)
{
	if (k >= w.size() || sum >= targetsum)
		return true;
	x[k] = true;
	if (sum + w[k] == targetsum)
		printSubsetSum(w, x);
	//include w[k]
	subsetSum(w, x, sum + w[k], targetsum, k + 1);
	//uninclude w[k]
	x[k] = false;
	subsetSum(w, x, sum, targetsum, k + 1);
	return false;
}
//increase order
bool subsetSum(const std::vector<int>& w, std::vector<bool> x, int targetsum, int n)//先返回元素少的
{
	if (n<0 || targetsum <= 0)
		return true;
	x[n] = true;
	if (targetsum == w[n])
		printSubsetSum(w, x);
	//include W[n]
	subsetSum(w, x, targetsum - w[n], n - 1);
	//uninclude W[n]
	x[n] = false;
	subsetSum(w, x, targetsum, n - 1);
	return false;
}

