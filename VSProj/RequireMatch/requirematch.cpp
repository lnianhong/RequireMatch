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
#include <numeric>
#include <list>
//using namespace std;
/******************************************************************/
// compare the priority level of the Items; 
bool compID(const Exchange_Item& Item1, const Exchange_Item& Item2)
{
	return Item1.getID() < Item2.getID();
}
bool compOrder(const Exchange_Item& Item1, const Exchange_Item& Item2)
{
	return Item1.getInitOrder() < Item2.getInitOrder();
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
bool readCSVdata(ExContainer& Rers, const std::string csvfilename)
{
	std::ifstream Rfile(csvfilename);
	CSVRow	Rrow;
	while (Rrow.readNextRow(Rfile))
	{
		//Exchange_Item tmp(row[0], atoi(row[1].c_str()));
		Rers.push_back(Exchange_Item(Rrow[0], atoi(Rrow[1].c_str())));
	}
	Rfile.close();
	return true;
}

bool readCSVdata(ExContainer& Rers, const std::string csvfilename,int startOrder)
{
	std::ifstream Rfile(csvfilename);
	CSVRow	Rrow;
	while (Rrow.readNextRow(Rfile))
	{
		//Exchange_Item tmp(row[0], atoi(row[1].c_str()));
		Rers.push_back(Exchange_Item(Rrow[0], atoi(Rrow[1].c_str()), startOrder));
		startOrder++;
	}
	Rfile.close();
	return true;
}

/*先排序然后通过移动“指针”的方式抵消重复的结果*/
size_t dealRepetition(ExContainer& Rers, ExContainer& Ters)
{
	int num_same(0);
	//sort(Rers.begin(), Rers.end(), compItemNoMaxWeight);
	//sort(Ters.begin(), Ters.end(), compItemNoMaxWeight);
	Rers.sort(compItemNoMaxWeight);
	Ters.sort(compItemNoMaxWeight);

	Itertype T_ptr = Ters.begin();

	for (Itertype Riter = Rers.begin() ; Riter != Rers.end() && T_ptr != Ters.end(); ++Riter)
	{
		if ((*Riter).getResMoney())
		{
			for (Itertype Titer = T_ptr; Titer != Ters.end(); ++Titer)
			{
				if ((*Riter).getResMoney() == (*Titer).getResMoney())
				{
					(*Riter).addExchangeInfo((*Titer).getID(), (*Riter).getResMoney());
					(*Riter).setResMoney(0);
					(*Riter).weightIncrease();

					(*Titer).addExchangeInfo((*Riter).getID(), (*Titer).getResMoney());
					(*Titer).setResMoney(0);
					(*Titer).weightIncrease();
					T_ptr++;
					num_same++;
					break;
				}
				else
				{
					if ((*Riter).getResMoney() > (*Titer).getResMoney())
						T_ptr++;
				}
			}
		}
	}
	return num_same;

}
/*获取已经处理完（Res_money==0）的条目*/
difftype finishedNum(ExContainer& Rers)
{
	Exchange_Item zeroItem("ZERO", 0);
	//Returns an iterator pointing to the first element in the range [first,last) 
	//which compares greater than val
	Itertype Rp = upper_bound(Rers.begin(), Rers.end(), zeroItem, compItemNoMaxWeight);
	difftype Rp0_num = distance(Rers.begin(),Rp);
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


// for mixed
void exchangeFunc(ExContainer& largeCont, ExContainer& smallCont,
				  ExSaver & largeSaver, ExSaver & smallSaver)
{
	Itertype it1, it2;
	Exchange_Item tmp, tmp1, tmp2;
	if (has2sum(smallCont.begin(), smallCont.end(), largeCont.back(), it1, it2))//it1 is in the front of it2
	{
		//set the exchange info
		largeCont.back().addExchangeInfo((*it1).getID(), (*it1).getResMoney());
		largeCont.back().addExchangeInfo((*it2).getID(), (*it2).getResMoney());
		largeCont.back().weightIncrease(2);
		largeCont.back().setResMoney(0);
		tmp = largeCont.back();
		(*it1).addExchangeInfo(tmp.getID(), (*it1).getResMoney());
		(*it1).weightIncrease();
		(*it1).setResMoney(0);
		(*it2).addExchangeInfo(tmp.getID(), (*it2).getResMoney());
		(*it2).weightIncrease();
		(*it2).setResMoney(0);
		//change the Ters 
		largeCont.pop_back();
		largeSaver.push_back(tmp);
		//change the Rers 
		smallSaver.push_back(*it2);
		smallSaver.push_back(*it1);
		smallCont.erase(it2);
		smallCont.erase(it1);
	}
	else //处理2个Item，一个为0，一个减小并插入（另一列中不会有相等的数）
	{
		largeCont.back().addExchangeInfo(smallCont.back().getID(), smallCont.back().getResMoney());
		largeCont.back().weightIncrease();
		largeCont.back().setResMoney(largeCont.back().getResMoney() - smallCont.back().getResMoney());

		smallCont.back().addExchangeInfo(largeCont.back().getID(), smallCont.back().getResMoney());
		smallCont.back().weightIncrease();
		smallCont.back().setResMoney(0);
		//change the largeCont 
		tmp = largeCont.back();
		largeCont.pop_back();
		// 插在第一个大于等于的值的前面
		Itertype iter_insert = lower_bound(largeCont.begin(), largeCont.end(), tmp, compItem);
		largeCont.insert(iter_insert, tmp);
		//change the smallCont
		smallSaver.push_back(smallCont.back());
		smallCont.pop_back();
	}
}


// get sum and maxium  of the exchange Times

std::vector<int> getExTimes(ExSaver& Rers)
{
	std::vector<int> ExTimes(Rers.size(), 0);
	int j(0);
	for (ExSaver::iterator i = Rers.begin(); i!= Rers.end(); i++)
	{
		ExTimes[j] = (*i).getWeight();
		j++;
	}
	return ExTimes;
}

int sumExTimes(ExSaver& Rers)
{
	std::vector<int> ExTimes = getExTimes(Rers);
	return std::accumulate(ExTimes.begin(), ExTimes.end(), 0);
}

ExSaver::iterator maxExTimes(ExSaver& Rers)
{
	std::vector<int> ExTimes = getExTimes(Rers);
	std::vector<int>::iterator it = std::max_element(ExTimes.begin(), ExTimes.end());
	ExSaver::iterator iter = Rers.begin();
	std::vector<int>::difference_type dist = distance(ExTimes.begin(), it);
	for (std::vector<int>::difference_type i = 0; i < dist; i++)
	{
		iter++;
	}
	return iter;
}



// write the result
void writeLog(std::string result_log, ExSaver& Rers, ExSaver& Ters, double t)
{
	std::ofstream outfile;
	outfile.open(result_log, std::ofstream::out);

	outfile << "Time:"<< t << " (s) " << std::endl;
	outfile << "Sum of exchange times:\t" << sumExTimes(Rers) << std::endl;
	outfile << "Maxium exchange times of Rers:\t" << (*maxExTimes(Rers)).getWeight() << std::endl;
	outfile << "Maxium exchange times of Ters:\t" << (*maxExTimes(Ters)).getWeight() << std::endl;
	outfile.close();
}

void writeResult(ExSaver& Rers,std::string result_file)
{
	std::ofstream outfile;
	outfile.open(result_file,std::ofstream::out);
	//typedef std::vector<std::string>::size_type exchange_ID_type;
	outfile << "User_ID,Money,ResMoney,Times,ExID1,"
		<< "Money1,ExID1,Money2,ExID3,Money3,ExID4,Money4,ExID5,Money5" << std::endl;

	for (ExSaver::iterator i = Rers.begin(); i != Rers.end(); i++)
	{
		outfile << (*i).getID() << ","
				<< (*i).getMoney() << ","
				<< (*i).getResMoney() << ","
				<< (*i).getWeight() << ",";
		for (int j = 0; j<(*i).getWeight(); j++)
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