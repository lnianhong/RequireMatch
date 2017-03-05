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
	if (Item1.getWeight() >= (Item1.maxWeight() - 1)) //Item1 �Ѵﵽ������
	{
		if (Item2.getWeight() > Item1.getWeight()) // Item2 �Ѵﵽ�������ҳ�ԽItem1
			return true;
		else //Item2.getWeight() <= Item1.getWeight()
		{
			if (Item2.getWeight() == Item1.getWeight()) 
				return compItemNoMaxWeight(Item1,Item2);// Item1 item2�ﵽ������
			else 
				return false;		
		}
	}
	else//Item1 δ�ﵽ������
	{	
		if (Item2.getWeight() >= (Item2.maxWeight() - 1)) // Item2 �Ѵﵽ������
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

bool readCSVdata(std::vector<Exchange_Item>& Rer, const std::string csvfilename,int startOrder)
{
	std::ifstream Rfile(csvfilename);
	CSVRow	Rrow;
	while (Rrow.readNextRow(Rfile))
	{
		//Exchange_Item tmp(row[0], atoi(row[1].c_str()));
		Rer.push_back(Exchange_Item(Rrow[0], atoi(Rrow[1].c_str()), startOrder));
		startOrder++;
	}
	Rfile.close();
	return true;
}

/*������Ȼ��ͨ���ƶ���ָ�롱�ķ�ʽ�����ظ��Ľ��*/
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
/*��ȡ�Ѿ������꣨Res_money==0������Ŀ*/
difftype finishedNum(std::vector<Exchange_Item>& Rer)
{
	Exchange_Item zeroItem("ZERO", 0);
	Itertype Rp = upper_bound(Rer.begin(), Rer.end(), zeroItem, compItemNoMaxWeight);
	difftype Rp0_num = distance(Rer.begin(),Rp);
	return Rp0_num;
}

/******************************************************************/
//�Ӽ�������
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

//��������
void exchangeFun(std::vector<Exchange_Item>& largeVec, std::vector<Exchange_Item>& smallVec,
				 difftype & Sp0_num,difftype & Lp0_num )
{
	Itertype it1, it2;
	Exchange_Item tmp, tmp1, tmp2;
	difftype dist1, dist2;

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
	else //����2��Item��һ��Ϊ0��һ����С�����루��һ���в�������ȵ�����
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
		// ���ڵ�һ�����ڵ��ڵ�ֵ��ǰ��
		Itertype iter_insert = lower_bound(largeVec.begin() + Lp0_num, largeVec.end(), tmp, compItem);
		largeVec.insert(iter_insert, tmp);
		//change the smallVec
		tmp1 = smallVec.back();
		smallVec.pop_back();
		smallVec.insert(smallVec.begin() + Sp0_num, tmp1);
		Sp0_num++;
	}
}

// get sum and maxium  of the exchange Times
std::vector<int> getExTimes(std::vector<Exchange_Item>& Rer)
{
	std::vector<int> ExTimes(Rer.size(), 0);
	int j(0);
	for (Itertype i = Rer.begin(); i < Rer.end(); i++)
	{
		ExTimes[j] = (*i).getWeight();
		j++;
	}
	return ExTimes;
}

int sumExTimes(std::vector<Exchange_Item>& Rer)
{
	std::vector<int> ExTimes = getExTimes(Rer);
	return std::accumulate(ExTimes.begin(), ExTimes.end(), 0);
}

Itertype maxExTimes(std::vector<Exchange_Item>& Rer)
{
	std::vector<int> ExTimes = getExTimes(Rer);
	std::vector<int>::iterator it = std::max_element(ExTimes.begin(), ExTimes.end());
	return Rer.begin() + distance(ExTimes.begin(),it);
}


void writeLog(std::string result_log, std::vector<Exchange_Item>& Rers, std::vector<Exchange_Item>& Ters, double t)
{
	std::ofstream outfile;
	outfile.open(result_log, std::ofstream::out);

	outfile << "Time:" << t << " (s) " << std::endl;
	outfile << "Sum of exchange times:\t" << sumExTimes(Rers) << std::endl;
	outfile << "Maxium exchange times of Rers:\t" << (*maxExTimes(Rers)).getWeight() << std::endl;
	outfile << "Maxium exchange times of Ters:\t" << (*maxExTimes(Ters)).getWeight() << std::endl;
	outfile.close();
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