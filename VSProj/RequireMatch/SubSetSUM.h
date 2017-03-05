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
bool subsetSum(const std::vector<int>& w, std::vector<bool> x, int sum, int targetsum, size_t k);
bool subsetSum(const std::vector<int>& w, std::vector<bool> x, int targetsum, int n);
void test_subsetsum();
#endif // !SUBSETSUM_H

