#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

//find if the given subset sum exists.
int findSubsetSum(vector<int>& arr, int given, vector<bool>& included)
{
	int cur = 0; // ָ��ǰֵ.
	int sum = 0; // ��ǰ�Ӽ��Ϻ�.

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
			** ��������ѭ�������ų�ƥ�䲻�ɹ��Ľ����
			** �����ڽ�����Լ��������ڽ���ڵ�Ԫ��
			** ֱ���ҵ���һ�������ڽ���ڵ�Ԫ��
			** ���磺��1��0��ʾ������δ����
			** �����Ϊ1110011���������1Ϊ����Ԫ��
			** �����Ϊ0�����Ǵӵ�4��0��ʼ������
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