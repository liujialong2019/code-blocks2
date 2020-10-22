#include <iostream>
#include <string>
using namespace std;
int main()
{
	int i = 0, j = 0, k1, k2;
	string str;
	char tmp;
	cout << "请输入一句话：";
	getline(cin, str);//输入一行
	while (str[i])
	{
		while (str[i] == ' ') i++;//跳过空格
		j = i;
		while (str[j] && str[j] != ' ')j++;//跳过字符串
		for (k1 = i, k2 = j - 1; k1 < k2;k1++, k2--)//逆转单词
		{
			tmp = str[k1];
			str[k1] = str[k2];
			str[k2] = tmp;
		}
		i = j;//使循环进入下一个单词
	}
	for (k1 = 0, k2 = i - 1; k1 < k2;k1++, k2--)
	{
		tmp = str[k1];
		str[k1] = str[k2];
		str[k2] = tmp;
	}
	cout << "单词逆序输出："<<str<<endl ;
	return 0;
}

