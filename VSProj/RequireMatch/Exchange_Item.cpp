#include "Exchange_Item.h"
#include <iostream>  
bool Exchange_Item::setID(std::string str)
{
	User_ID = str;
	return true;
}

std::string Exchange_Item::getID() const
{
	return User_ID;
}

bool Exchange_Item::setMoney(int w)
{
	money = w;
	return true;
}
int Exchange_Item::getMoney() const
{
	return money;
}
bool Exchange_Item::setWeight(int w) 
{
	weight = w;
	return true;
}
int Exchange_Item::getWeight() const
{
	return weight;
}
bool Exchange_Item::weightIncrease()
{
	weight = weight + 1;
	return true;
}
bool Exchange_Item::weightIncrease(int i)
{
	weight = weight + i;
	return true;
}
bool Exchange_Item::setResMoney(int res) 
{
	res_money = res;
	return true;
}
int Exchange_Item::getResMoney() const 
{
	return res_money;
}
bool Exchange_Item::addExchangeInfo(std::string str, int m)
{
	exchange_ID.push_back(str);
	exchange_money.push_back(m);
	return true;

}
std::map<std::string, int> Exchange_Item::getExchangeInfo()
{
	typedef std::vector<std::string>::size_type exchange_ID_type;
	typedef std::map<std::string, int>::value_type valType;
	std::map<std::string, int> ExchangeInfo;
	if (exchange_ID.size())
	{
		for (exchange_ID_type i=0;i<exchange_ID.size();++i)
		{
			ExchangeInfo.insert(valType(exchange_ID[i], exchange_money[i]));
		}
	}
	return ExchangeInfo;

}
int Exchange_Item::maxWeight() const
{
	return max_weight;
}

void Exchange_Item::print() 
{
	std::cout << "User_ID:" << User_ID << std::endl;
	std::cout << "Money:" << money << "\t"
			  <<"Res_M:" << res_money << std::endl;
	typedef std::vector<std::string>::size_type exchange_ID_type;
	if (exchange_ID.size())
	{
		for (exchange_ID_type i = 0; i<exchange_ID.size(); ++i)
		{
			std::cout << "exchange_ID:" << exchange_ID[i] << "\t" 
				      << "exchange_money:" << exchange_money[i]<<std::endl;
		}
	}
	std::cout << std::endl;
}