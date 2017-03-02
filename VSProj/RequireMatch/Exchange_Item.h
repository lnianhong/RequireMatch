#pragma once
#ifndef EXCHANGEITEM 
#define EXCHANGEITEM 
#include<string>
#include<vector>
#include<map>
class Exchange_Item
{
public:
	Exchange_Item() : User_ID("000000"), money(0), res_money(0), weight(0), max_weight(5) {};//default construct function
	Exchange_Item(const std::string str,int m,int res_m,int w,int max_w) : \
		User_ID(str), money(m), res_money(res_m), weight(w), max_weight(max_w) {};
	Exchange_Item( const std::string str, int m) : \
		User_ID(str), money(m), res_money(m), weight(0), max_weight(5) {};
	//virtual ~Exchange_Item();
	Exchange_Item(const Exchange_Item&) = default;
	Exchange_Item& operator=(const Exchange_Item&) = default;

	bool setID(std::string str);
	std::string getID() const;
	bool setMoney(int m);
	int getMoney() const;
	bool setWeight(int w);
	int getWeight() const;
	bool weightIncrease();
	bool weightIncrease(int i);
	bool setResMoney(int res);
	int getResMoney() const;
	bool addExchangeInfo(std::string str, int m);
	std::map<std::string, int> getExchangeInfo();
	int maxWeight() const;
	void print();

private:
	std::string User_ID;
	int money;
	int res_money;
	int weight;
	int max_weight;
	std::vector<std::string> exchange_ID;
	std::vector<int> exchange_money;

};

#endif // !EXCHANGEITEM ;


