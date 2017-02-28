#include <iostream>  
#include <vector>  
#include <bitset>  

using namespace std;

void print(const vector<int> & W,const bitset<5> & X)
{
	cout << "{";
	for (int i = 0; i < X.size(); ++i) 
	{
		if (X[i])
		{
			cout << W[i] << " ";
		}	
	}
	cout << "}";
	cout << endl;
}
bool subsetSum(const vector<int>& W, bitset<5>& X, int sum, int targetSum, int k) 
{
	X[k] = 1; // try one branch of tree  
	if (sum + W[k] == targetSum)
		print(W,X); // we have a solution  
	else
	{
		if (k + 1 < W.size() && sum + W[k] <= targetSum) // include the W[k]
			subsetSum(W, X, sum + W[k], targetSum, k + 1); // the maxium k is W.size-2
		if (k + 1 < W.size() && sum + W[k + 1] <= targetSum)
		{
			X[k] = 0; // uniclude the W[k]
			subsetSum(W, X, sum, targetSum, k + 1); // the maxium k is W.size-2
		}
	}
	return true;

}


int main() {
	//int arr[] = { 2,5,15,8,20 };
	//vector<int> v(arr, arr + sizeof(arr) / sizeof(int));
	//vector<bool> included(sizeof(arr) / sizeof(int), false);

	vector<int> W = { 2, 4, 6, 8, 10 };
	bitset<5> X;
	subsetSum(W, X, 0, 20, 0);
	system("pause");
	return 0;
}
