#include<ios>
#include<stdio.h>
//using namespace std;
int main()
{
	string str;
	getline(cin,str);//输入一行
	int i = 0;
	while(str[i]!='\0')
        i++;
    for(int i1=i-1;i1>=0;i1--)
    {
        int j = i1;
        int i2=0;
        while(str[i1]!=' '&&i1!=-1)//考虑到向前读到第一个单词时
        {
            i2++;
            i1--;
        }
        for(int i3=0;i3<i2;i3++)
            cout<<str[j-i2+1+i3];
        if(i1!=-1)//最后一个单词后面无空格
            cout<<" ";
    }
}
