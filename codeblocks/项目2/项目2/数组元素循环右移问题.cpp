#include<iostream>
using namespace std;
int main()
{
    int n;
    int d;
    cin>>n>>d;
    int array0[n];
    for(int i=0;i<n;i++)
        cin>>array0[i];
    //控制输出而不必移动数组元素
    int weiyi = d%n;
    //考虑位移为零的情况
    if(weiyi==0)
        for(int i=0;i<n;i++)
    {
        if(i==n-1)
            cout<<array0[i];
        else
            cout<<array0[i]<<" ";
    }
    else
    {
        for(int i=0;i<weiyi;i++)
            cout <<array0[n-weiyi+i]<<" ";
        for(int i=0;i<n-weiyi;i++)
        {
            if(i==n-weiyi-1)
                cout<<array0[i];
            else
                cout<<array0[i]<<" ";
        }
    }

    return 0;
}

