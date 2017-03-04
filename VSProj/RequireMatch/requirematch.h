#pragma once
#ifndef REQUIREMATCH_h
#define REQUIREMATCH_h
#include"Exchange_Item.h"
#include <vector> 
#include <list> 
#include <string>

typedef std::list<Exchange_Item> ExContainer;
typedef ExContainer::iterator Itertype;
typedef ExContainer::difference_type difftype;
//typedef std::vector<Exchange_Item>::iterator Itertype;
//typedef std::vector<Exchange_Item>::difference_type difftype;


bool compID(const Exchange_Item& Item1, const Exchange_Item& Item2);
bool compOrder(const Exchange_Item& Item1, const Exchange_Item& Item2);
bool compItemNoMaxWeight(const Exchange_Item& Item1, const Exchange_Item& Item2);
bool compItem(const Exchange_Item& Item1, const Exchange_Item& Item2);

bool readCSVdata(ExContainer& Rers, const std::string csvfilename);
bool readCSVdata(ExContainer& Rers, const std::string csvfilename, int startOrder);
size_t dealRepetition(ExContainer& Rers, ExContainer& Ters);
difftype finishedNum(ExContainer& Rers);

void printSubsetSum(const std::vector<int> & w, const std::vector<bool>& x);
bool subsetSum(const std::vector<int>& w, std::vector<bool> x, int sum, int targetsum, size_t k);
bool subsetSum(const std::vector<int>& w, std::vector<bool> x, int targetsum, int n);
bool has2sum(Itertype& first, Itertype& last, Exchange_Item& target, Itertype& it1, Itertype& it2);
Itertype listIterAdd(Itertype iter, difftype n);
void exchangeFunc(ExContainer& largeCont, ExContainer& smallCont,
					difftype & Sp0_num,difftype & Lp0_num);
std::vector<int> getExTimes(ExContainer& Rers);
int sumExTimes(ExContainer& Rers);
Itertype maxExTimes(ExContainer& Rers);
void writeResult(ExContainer& Rers, std::string result_file);
void writeLog(std::string result_log, ExContainer& Rers, ExContainer& Ters, double t);
//class Solution {
//public:
//	vector&lt; vector &gt; findZeroSumInSortedArr(vector &num, int begin, int count, int target)
//	{
//		vector ret;
//		vector tuple;
//		set visited;
//		if (count == 2)
//		{
//			int i = begin, j = num.size() - 1;
//			while (i &lt; j)
//			{
//				int sum = num[i] + num[j];
//				if (sum == target && visited.find(num[i]) == visited.end())
//				{
//					tuple.clear();
//					visited.insert(num[i]);
//					visited.insert(num[j]);
//					tuple.push_back(num[i]);
//					tuple.push_back(num[j]);
//					ret.push_back(tuple);
//					i++; j¨C;
//				}
//				else if (sum &lt; target)
//				{
//					i++;
//				}
//				else
//				{
//					j¨C;
//				}
//			}
//		}
//		else
//		{
//			for (int i = begin; i&lt; num.size(); i++)
//			{
//				if (visited.find(num[i]) == visited.end())
//				{
//					visited.insert(num[i]);
//					vector subRet = findZeroSumInSortedArr(num, i + 1, count - 1, target - num[i]);
//					if (!subRet.empty())
//					{
//						for (int j = 0; j&lt; subRet.size(); j++)
//						{
//							subRet[j].insert(subRet[j].begin(), num[i]);
//						}
//
//						ret.insert(ret.end(), subRet.begin(), subRet.end());
//					}
//				}
//			}
//		}
//
//		return ret;
//	}
//
//	vector threeSum(vector &num) {
//		sort(num.begin(), num.end());
//		return findZeroSumInSortedArr(num, 0, 3, 0);
//	}
//
//	vector fourSum(vector &num, int target) {
//		sort(num.begin(), num.end());
//		return findZeroSumInSortedArr(num, 0, 4, target);
//	}
//};

#endif // !REQUIREMATCH_h


