#pragma once
#include<string>
#include<vector>
class Exchange_Item
{
public:
	Exchange_Item();
	virtual ~Exchange_Item();
	bool setID();
	std::string getID() const;
	bool setMoney();
	int getMoney() const;
	bool setWeight();
	int getWeight() const;
	bool weightIncrease();
	bool setResMoney();
	int getResMoney() const;
	bool addExchangeInfo();
	bool getExchangeInfo();
	void print();



private:
	std::string User_ID;
	int money;
	int res_money;
	int weight;
	std::vector<std::string> exchange_ID;
	std::vector<int> exchange_money;


};

