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
//Itertype listIterAdd(Itertype iter, difftype n);
//void exchangeFunc(ExContainer& largeCont, ExContainer& smallCont,
//					difftype & Sp0_num,difftype & Lp0_num);

void exchangeFunc(ExContainer& largeCont, ExContainer& smallCont,
	ExSaver & largeSaver, ExSaver & smallSaver);

// write and analysis the result
std::vector<int> getExTimes(ExSaver& Rers);

int sumExTimes(ExSaver& Rers);

ExSaver::iterator maxExTimes(ExSaver& Rers);


void writeResult(ExSaver& Rers, std::string result_file);


void writeLog(std::string result_log, ExSaver& Rers, ExSaver& Ters, double t);


#endif // !REQUIREMATCH_h


