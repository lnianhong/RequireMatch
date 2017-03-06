#pragma once
#ifndef REQUIREMATCH_h
#define REQUIREMATCH_h
#include"Exchange_Item.h"
#include <vector> 
#include <list> 
#include <string>

typedef std::list<Exchange_Item> ExContainer;
typedef std::list<Exchange_Item> ExSaver;
typedef ExContainer::iterator Itertype;
typedef ExContainer::difference_type difftype;


bool compID(const Exchange_Item& Item1, const Exchange_Item& Item2);
bool compOrder(const Exchange_Item& Item1, const Exchange_Item& Item2);
bool compItemNoMaxWeight(const Exchange_Item& Item1, const Exchange_Item& Item2);
bool compItem(const Exchange_Item& Item1, const Exchange_Item& Item2);

bool readCSVdata(ExContainer& Rers, const std::string csvfilename);
bool readCSVdata(ExContainer& Rers, const std::string csvfilename, int startOrder);
size_t dealRepetition(ExContainer& Rers, ExContainer& Ters);
difftype finishedNum(ExContainer& Rers);


bool has2sum(Itertype& first, Itertype& last, Exchange_Item& target, Itertype& it1, Itertype& it2);


void exchangeFunc(ExContainer& largeCont, ExContainer& smallCont,
	ExSaver & largeSaver, ExSaver & smallSaver);


std::vector<int> getExTimes(ExSaver& Rers);
int sumExTimes(ExSaver& Rers);
ExSaver::iterator maxExTimes(ExSaver& Rers);
void writeResult(ExSaver& Rers, std::string result_file);
void writeLog(std::string result_log, ExSaver& Rers, ExSaver& Ters, double t);


#endif // !REQUIREMATCH_h


//bool compID(const Exchange_Item& Item1, const Exchange_Item& Item2);
////比较用户ID，也就是字符串比较，第一个比第二个小则返回true
//
//bool compOrder(const Exchange_Item& Item1, const Exchange_Item& Item2);
////比较用户原始输入顺序，第一个的order比第二个order小则返回true
//
//bool compItemNoMaxWeight(const Exchange_Item& Item1, const Exchange_Item& Item2);
////不考虑权重，仅仅比较余额，第一个余额小，则返回true
//
//bool compItem(const Exchange_Item& Item1, const Exchange_Item& Item2);
////考虑权重进行比较
//
//bool readCSVdata(ExContainer& Rers, const std::string csvfilename);
//// 从CSV读取数据到list容器中
//bool readCSVdata(ExContainer& Rers, const std::string csvfilename, int startOrder);
//// 从CSV读取数据到list容器中并给定初始顺序标号
//
//size_t dealRepetition(ExContainer& Rers, ExContainer& Ters);
//// 先排序，Rers和Ters中可以抵消的数据发生抵消并记录，返回抵消的笔数
//difftype finishedNum(ExContainer& Rers);
//// 获取liast中余额为0个个数
//
//bool has2sum(Itertype& first, Itertype& last, Exchange_Item& target, Itertype& it1, Itertype& it2);
//// 在迭代器指定范围[first,last)内，查找是否有两个元素的余额的和与target的余额相等
////如果有则将指向两元素迭代器赋给it1和it2，并返回true
//
//void exchangeFunc(ExContainer& largeCont, ExContainer& smallCont,
//	ExSaver & largeSaver, ExSaver & smallSaver);
////两个容器中元素发生交易，将完成交易的存储在另一容器并从原先容器中删除
//
//std::vector<int> getExTimes(ExSaver& Rers);
//// 返回每个元素的交易次数的容器
//
//int sumExTimes(ExSaver& Rers);
//// 返回总交易次数
//
//ExSaver::iterator maxExTimes(ExSaver& Rers);
//// 返回最大交易次数
//
//void writeResult(ExSaver& Rers, std::string result_file);
////将结果写进CSV
//
//void writeLog(std::string result_log, ExSaver& Rers, ExSaver& Ters, double t);
////将运行时间，最大交易次数，总交易次数写进log