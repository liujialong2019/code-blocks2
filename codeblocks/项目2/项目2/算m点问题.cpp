#include<string>
#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
int a[10001];
int book[10001];//标记a数组i下表的数字是否使用过
int n;//正整数的个数
int m;//待求得数字
int flag;//题目要求只输出一组解，用于标记是否找到了一组可行解
//表示搜索到第step层，并且前step-1层算式的值是value
bool dfs(int  step, int value)
{
	//剪枝：如果已经找到一组可行解，不再进行搜索
	if (flag)return false;
	//搜索到第n+1层
	if (step == n + 1)
	{
		//如果满足题目要求
		if (value == m)
		{
			flag = 1;
			return true;
		}
		//否则返回false
		else return false;
	}
	for (int i = 1; i <= n; i++)
	{
		//如果下表为i的数字没有使用过
		if (!book[i])
		{
			//标记
			book[i] = 1;
			//搜索下一层
			if (dfs(step + 1, value + a[i]))
			{
				//回溯输出，只有当满足题意返回值为true时才进行输出，否则不输出
				if (step != 1)
				{
					cout << value << "+" << a[i] << "=" << value + a[i] << ";"<< endl;
				}
				return true;
			}
			if (dfs(step + 1, value - a[i]))
			{
				if (step != 1)
				{
					cout << value << "-" << a[i] << "=" << value - a[i] << ";"<< endl;
				}
				return true;
			}
			if (dfs(step + 1, value * a[i]))
			{
				if (step != 1)
				{
					cout << value << "*" << a[i] << "=" << value * a[i] << ";"<< endl;
				}
				return true;
			}
			if (dfs(step + 1, value / a[i]))
			{
				if (step != 1)
				{
					cout << value << "/" << a[i] << "=" << value / a[i] << ";"<< endl;
				}
				return true;
			}
			//回溯，标记清零
			book[i] = 0;
		}
	}
	return false;
}
int main()
{
	cin >> n >> m;
	for (int i = 1; i <= n; i++)
	{
		cin >> a[i];
	}
	dfs(1, 0);
	//果没有找到一组解
	if (!flag)
	{
		cout<<"No Solution"<<endl;
	}
	return 0;
}

