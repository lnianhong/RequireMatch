#pragma once
#ifndef REQUIREMATCH_h
#define REQUIREMATCH_h
#include"Exchange_Item.h"
#include <vector>  
#include <string>
bool compItemNoMaxWeight(const Exchange_Item& Item1, const Exchange_Item& Item2);
bool compItem(const Exchange_Item& Item1, const Exchange_Item& Item2);

bool readCSVdata(std::vector<Exchange_Item>& Rer, const std::string csvfilename);
int dealRepetition(std::vector<Exchange_Item>& Rer, std::vector<Exchange_Item>& Ter);
std::vector<Exchange_Item>::size_type finishedNum(std::vector<Exchange_Item>& Rer);

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


