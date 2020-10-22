#include<iostream>
#include <algorithm>
using namespace std;
int main()
{
    int i = 0;
    int guest[100];
    int x;
    while(cin>>x)//这种输入有问题
    {
        guest[i] = x;
        i++;
    }
    int gt[i];
    for(int j=0;j<i;j++)
        gt[j] = guest[j];
    sort(gt,gt+i);//使用自带的排序函数
    x = 0;
    for(int j=0;j<i;j++)
        x = x + gt[j]*(i-j);
    cout<<"需要的总时间为"<<x;
    return 0;
}
