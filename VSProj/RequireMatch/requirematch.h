#pragma once
#ifndef REQUIREMATCH_h
#define REQUIREMATCH_h
#include"Exchange_Item.h"
bool compItemNoMaxWeight(const Exchange_Item& Item1, const Exchange_Item& Item2);
bool compItem(const Exchange_Item& Item1, const Exchange_Item& Item2);

bool readCSVdata(std::vector<Exchange_Item>& Rer, const std::string csvfilename);
#endif // !REQUIREMATCH_h


