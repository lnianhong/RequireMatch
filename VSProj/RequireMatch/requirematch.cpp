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

/*������Ȼ��ͨ���ƶ���ָ�롱�ķ�ʽ�����ظ��Ľ��*/
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
/*��ȡ�Ѿ������꣨Res_money==0������Ŀ*/
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

//�ȷ���Ԫ�ض��
//decrease order
bool subsetSum(const std::vector<int>& w, std::vector<bool> x, int sum, int targetsum, size_t k)
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
bool subsetSum(const std::vector<int>& w, std::vector<bool> x, int targetsum, int n)//�ȷ���Ԫ���ٵ�
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

Itertype listIterAdd(Itertype iter, difftype n)
{
	if (n > 0)
	{
		for (difftype i = 1; i <= n; i++)
		{
			iter++;
		}
	}
	else 
	{
		for (difftype i = n; i < 0; i++)
		{
			iter--;
		}
	}
	return iter;
}

//��������
void exchangeFunc(ExContainer& largeCont, ExContainer& smallCont,
				 difftype & Sp0_num,difftype & Lp0_num )
{
	Itertype it1, it2;
	Exchange_Item tmp, tmp1, tmp2;
	if (has2sum(listIterAdd(smallCont.begin(), Sp0_num), smallCont.end(), largeCont.back(), it1, it2))//it1 is in the front of it2
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
		tmp1 = (*it1);
		tmp2 = (*it2);
		//change the Ters 
		largeCont.pop_back();
		largeCont.insert(listIterAdd(largeCont.begin(), Lp0_num), tmp);
		Lp0_num++;
		//change the Rers 
		smallCont.erase(it2);
		smallCont.erase(it1);
		Itertype it_insert1 = smallCont.insert(listIterAdd(smallCont.begin(), Sp0_num), tmp2);
		Sp0_num++;
		smallCont.insert(it_insert1, tmp1);
		Sp0_num++;
	}
	else //����2��Item��һ��Ϊ0��һ����С�����루��һ���в�������ȵ�����
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
		// ���ڵ�һ�����ڵ��ڵ�ֵ��ǰ��
		Itertype iter_insert = lower_bound(listIterAdd(largeCont.begin(), Lp0_num), largeCont.end(), tmp, compItem);
		largeCont.insert(iter_insert, tmp);
		//change the smallCont
		tmp1 = smallCont.back();
		smallCont.pop_back();
		smallCont.insert(listIterAdd(smallCont.begin(), Sp0_num), tmp1);
		Sp0_num++;
	}
}

// get sum and maxium  of the exchange Times
std::vector<int> getExTimes(ExContainer& Rers)
{
	std::vector<int> ExTimes(Rers.size(), 0);
	int j(0);
	for (Itertype i = Rers.begin(); i!= Rers.end(); i++)
	{
		ExTimes[j] = (*i).getWeight();
		j++;
	}
	return ExTimes;
}

int sumExTimes(ExContainer& Rers)
{
	std::vector<int> ExTimes = getExTimes(Rers);
	return std::accumulate(ExTimes.begin(), ExTimes.end(), 0);
}

Itertype maxExTimes(ExContainer& Rers)
{
	std::vector<int> ExTimes = getExTimes(Rers);
	std::vector<int>::iterator it = std::max_element(ExTimes.begin(), ExTimes.end());
	Itertype iter = listIterAdd(Rers.begin(), distance(ExTimes.begin(), it));
	return iter;
}



// write the result

void writeLog(std::string result_log, ExContainer& Rers, ExContainer& Ters, double t)
{
	std::ofstream outfile;
	outfile.open(result_log, std::ofstream::out);

	outfile << "Time:"<< t << " (s) " << std::endl;
	outfile << "Sum of exchange times:\t" << sumExTimes(Rers) << std::endl;
	outfile << "Maxium exchange times of Rers:\t" << (*maxExTimes(Rers)).getWeight() << std::endl;
	outfile << "Maxium exchange times of Ters:\t" << (*maxExTimes(Ters)).getWeight() << std::endl;
	outfile.close();
}
void writeResult(ExContainer& Rers,std::string result_file)
{
	std::ofstream outfile;
	outfile.open(result_file,std::ofstream::out);
	//typedef std::vector<std::string>::size_type exchange_ID_type;
	outfile << "User_ID,Money,ResMoney,Times,ExID1,"
		<< "Money1,ExID1,Money2,ExID3,Money3,ExID4,Money4,ExID5,Money5" << std::endl;

	for (Itertype i = Rers.begin(); i != Rers.end(); i++)
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