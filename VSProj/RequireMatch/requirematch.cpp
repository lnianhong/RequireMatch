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
#include <fstream>
#include <iostream>
//using namespace std;
/******************************************************************/
// compare the priority level of the Items; 
bool compID(const Exchange_Item& Item1, const Exchange_Item& Item2)
{
	return Item1.getID() < Item2.getID();
}
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
				return compItemNoMaxWeight(Item1,Item2);// Item1 item2达到最大次数
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

//交换问题
void exchangeFun(std::vector<Exchange_Item>& largeVec, std::vector<Exchange_Item>& smallVec,
				 std::vector<Exchange_Item>::difference_type & Sp0_num,
				 std::vector<Exchange_Item>::difference_type & Lp0_num )
{
	Itertype it1, it2;
	Exchange_Item tmp, tmp1, tmp2;
	std::vector<Exchange_Item>::difference_type dist1, dist2;

	if (has2sum(smallVec.begin() + Sp0_num, smallVec.end(), largeVec.back(), it1, it2))//it1 is in the front of it2
	{
		//set the exchange info
		largeVec.back().addExchangeInfo((*it1).getID(), (*it1).getResMoney());
		largeVec.back().addExchangeInfo((*it2).getID(), (*it2).getResMoney());
		largeVec.back().weightIncrease(2);
		largeVec.back().setResMoney(0);
		tmp = largeVec.back();
		(*it1).addExchangeInfo(tmp.getID(), (*it1).getResMoney());
		(*it1).weightIncrease();
		(*it1).setResMoney(0);
		(*it2).addExchangeInfo(tmp.getID(), (*it2).getResMoney());
		(*it2).weightIncrease();
		(*it2).setResMoney(0);
		tmp1 = (*it1);
		tmp2 = (*it2);
		dist1 = distance(smallVec.begin(), it1);
		dist2 = distance(smallVec.begin(), it2);
		//change the Ters 
		largeVec.pop_back();
		largeVec.insert(largeVec.begin() + Lp0_num, tmp);
		Lp0_num++;
		//change the Rers 
		smallVec.erase(smallVec.begin() + dist2);
		smallVec.erase(smallVec.begin() + dist1);
		smallVec.insert(smallVec.begin() + Sp0_num, tmp2);
		Sp0_num++;
		smallVec.insert(smallVec.begin() + Sp0_num, tmp1);
		Sp0_num++;
	}
	else //处理2个Item，一个为0，一个减小并插入（另一列中不会有相等的数）
	{
		largeVec.back().addExchangeInfo(smallVec.back().getID(), smallVec.back().getResMoney());
		largeVec.back().weightIncrease();
		largeVec.back().setResMoney(largeVec.back().getResMoney() - smallVec.back().getResMoney());

		smallVec.back().addExchangeInfo(largeVec.back().getID(), smallVec.back().getResMoney());
		smallVec.back().weightIncrease();
		smallVec.back().setResMoney(0);
		//change the largeVec 
		tmp = largeVec.back();
		largeVec.pop_back();
		// 插在第一个大于等于的值的前面
		Itertype iter_insert = lower_bound(largeVec.begin() + Lp0_num, largeVec.end(), tmp, compItem);
		largeVec.insert(iter_insert, tmp);
		//change the smallVec
		tmp1 = smallVec.back();
		smallVec.pop_back();
		smallVec.insert(smallVec.begin() + Sp0_num, tmp1);
		Sp0_num++;
	}
}
// write the result
void writeResult(std::vector<Exchange_Item>& Rer,std::string result_file)
{
	std::ofstream outfile;
	outfile.open(result_file,std::ofstream::out);
	typedef std::vector<std::string>::size_type exchange_ID_type;
	outfile << "User_ID,Money,ResMoney,Times,ExID1,"
		<< "Money1,ExID1,Money2,ExID3,Money3,ExID4,Money4,ExID5,Money5" << std::endl;

	for (Itertype i = Rer.begin(); i < Rer.end(); i++)
	{
		outfile << (*i).getID() << ","
				<< (*i).getMoney() << ","
				<< (*i).getResMoney() << ","
				<< (*i).getWeight() << ",";
		for (exchange_ID_type j = 0; j<(*i).getWeight(); j++)
		{
			if (j== (*i).getWeight()-1) //the last one
			{
				outfile << ((*i).getExchangeID())[j] << ","
					<< ((*i).getExchangeMoney())[j] ;
			}
			else
			{
				outfile << ((*i).getExchangeID())[j] << ","
					<< ((*i).getExchangeMoney())[j] << ",";
			}			
		}
		outfile << std::endl;
	}
	outfile.close();
}