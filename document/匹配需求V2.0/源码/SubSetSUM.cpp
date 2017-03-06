#include "SubSetSUM.h"


//subsetsum
void printSubsetSum(const std::vector<int> & w, const std::vector<bool>& x)
{
	std::cout << "{";
	for (unsigned int i = 0; i < x.size(); ++i)
	{
		if (x[i])
		{
			std::cout << w[i] << " ";
		}
	}
	std::cout << "}";
	std::cout << std::endl;
}

//先返回元素多的
//decrease order
bool subsetSum(const std::vector<int>& w, std::vector<bool> x, int sum, int targetsum, size_t k)
{
	if (k >= w.size() || sum >= targetsum)
		return true;
	x[k] = true;
	if (sum + w[k] == targetsum)
		printSubsetSum(w, x);
	//include w[k]
	subsetSum(w, x, sum + w[k], targetsum, k + 1);
	//uninclude w[k]
	x[k] = false;
	subsetSum(w, x, sum, targetsum, k + 1);
	return false;
}
//increase order
bool subsetSum(const std::vector<int>& w, std::vector<bool> x, int targetsum, int n)//先返回元素少的
{
	if (n<0 || targetsum <= 0)
		return true;
	x[n] = true;
	if (targetsum == w[n])
		printSubsetSum(w, x);
	//include W[n]
	subsetSum(w, x, targetsum - w[n], n - 1);
	//uninclude W[n]
	x[n] = false;
	subsetSum(w, x, targetsum, n - 1);
	return false;
}


void test_subsetsum() {

	int arr[] = { 1,2,3,4,5,6,7,8,9,10,11,12,13,14,20 };
	std::vector<int> w(arr, arr + sizeof(arr) / sizeof(int));
	std::vector<bool> included(sizeof(arr) / sizeof(int), false);
	std::vector<bool> includedv2(sizeof(arr) / sizeof(int), false);
	std::cout << "*********decrease order********" << std::endl;
	subsetSum(w, included, 0, 20, 0);//decrease order
	std::cout << "*********increase order********" << std::endl;
	subsetSum(w, includedv2, 20, w.size()-1);//increase order
}