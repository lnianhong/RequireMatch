#pragma once
#ifndef REQUIREMATCH_h
#define REQUIREMATCH_h
#include"Exchange_Item.h"
#include <vector>  
#include <string>

typedef std::vector<Exchange_Item>::iterator Itertype;
typedef std::vector<Exchange_Item>::difference_type difftype;

bool compID(const Exchange_Item& Item1, const Exchange_Item& Item2);
bool compOrder(const Exchange_Item& Item1, const Exchange_Item& Item2);
bool compItemNoMaxWeight(const Exchange_Item& Item1, const Exchange_Item& Item2);
bool compItem(const Exchange_Item& Item1, const Exchange_Item& Item2);

bool readCSVdata(std::vector<Exchange_Item>& Rer, const std::string csvfilename);
bool readCSVdata(std::vector<Exchange_Item>& Rer, const std::string csvfilename, int startOrder);
int dealRepetition(std::vector<Exchange_Item>& Rer, std::vector<Exchange_Item>& Ter);
difftype finishedNum(std::vector<Exchange_Item>& Rer);

bool has2sum(Itertype& first, Itertype& last, Exchange_Item& target, Itertype& it1, Itertype& it2);
void exchangeFun(std::vector<Exchange_Item>& largeVec, std::vector<Exchange_Item>& smallVec,
					difftype & Sp0_num,difftype & Lp0_num);
std::vector<int> getExTimes(std::vector<Exchange_Item>& Rer);
int sumExTimes(std::vector<Exchange_Item>& Rer);
Itertype maxExTimes(std::vector<Exchange_Item>& Rer);
void writeResult(std::vector<Exchange_Item>& Rer, std::string result_file);
void writeLog(std::string result_log, std::vector<Exchange_Item>& Rers, std::vector<Exchange_Item>& Ters, double t);

#endif // !REQUIREMATCH_h


