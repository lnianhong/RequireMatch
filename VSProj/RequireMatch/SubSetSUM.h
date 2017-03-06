#pragma once
#ifndef SUBSETSUM_H
#define SUBSETSUM_H
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

void printSubsetSum(const std::vector<int> & w, const std::vector<bool>& x);
//输出已经找到的符合要求的子集

bool subsetSum(const std::vector<int>& w, std::vector<bool> x, int sum, int targetsum, size_t k);
//寻找子集和的函数，先寻找元素较多的子集

bool subsetSum(const std::vector<int>& w, std::vector<bool> x, int targetsum, int n);
////寻找子集和的函数，先寻找元素较少的子集

void test_subsetsum();
//测试 printSubsetSum函数，subsetSum函数
#endif // !SUBSETSUM_H

