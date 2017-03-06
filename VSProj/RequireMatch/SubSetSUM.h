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
//����Ѿ��ҵ��ķ���Ҫ����Ӽ�

bool subsetSum(const std::vector<int>& w, std::vector<bool> x, int sum, int targetsum, size_t k);
//Ѱ���Ӽ��͵ĺ�������Ѱ��Ԫ�ؽ϶���Ӽ�

bool subsetSum(const std::vector<int>& w, std::vector<bool> x, int targetsum, int n);
////Ѱ���Ӽ��͵ĺ�������Ѱ��Ԫ�ؽ��ٵ��Ӽ�

void test_subsetsum();
//���� printSubsetSum������subsetSum����
#endif // !SUBSETSUM_H

