#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

//find if the given subset sum exists.
int findSubsetSum(vector<int>& arr, int given, vector<bool>& included)
{
	int cur = 0; // 指向当前值.
	int sum = 0; // 当前子集合和.

	while (cur >= 0)
	{
		//if current one is not included
		if (false == included[cur])
		{
			//include current one
			included[cur] = true;
			sum += arr[cur];
			//find the given subset sum
			if (sum == given)
			{
				return 1;
			}
			else if (sum > given) //exceed the given sum
			{
				included[cur] = false;
				sum -= arr[cur];
			}
			cur++;
		}
		//backtrace
		if (cur >= arr.size())
		{
			/*
			** 下面两个循环依次排除匹配不成功的结果中
			** 包括在结果内以及不包括在结果内的元素
			** 直到找到下一个包括在结果内的元素
			** 例如：用1和0表示包括和未包括
			** 若结果为1110011，则第三个1为所找元素
			** 将其变为0，但是从第4个0开始遍历。
			**/
			while (true == included[cur - 1])
			{
				cur--;
				included[cur] = false;
				sum -= arr[cur];
				//backtrace to the head
				if (cur < 1)
					return 0;
			}
			while (false == included[cur - 1])
			{
				cur--;
				if (cur < 1)
					return 0;
			}
			//change the status of current - 1,not current!
			included[cur - 1] = false;
			sum -= arr[cur - 1];
		}
	}
	return 0;
}



int main()
{
	int arr[] = { 2,5,15,8,20 };
	vector<int> v(arr, arr + sizeof(arr) / sizeof(int));
	vector<bool> included(sizeof(arr) / sizeof(int), false);
	int given = 33;//5+8+20

	if (findSubsetSum(v, given, included))
	{
		vector<bool>::iterator iterb = included.begin();
		vector<int>::iterator iteri = v.begin();
		for (; iterb != included.end(); iterb++, iteri++)
		{
			if (*iterb)
				cout << *iteri << endl;
		}
	}
	system("pause");

}