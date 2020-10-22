#include<iostream>
using namespace std;
int main()
{
    int n;
    int i,j,k;
    cin>>n;
    if(n<10)
    {
        for(i=1;i<=n;i++)
            cout<<i;
    }
    if(n>=10&&n<99)
    {
        int a = n%10;
        int b = n/10;
        for(i=0;i<b;i++)
            cout<<"S";
        for(j=1;j<=a;j++)
            cout<<j;
    }
    if(n>=100&&n<1000)
    {
      int a = n%10;
      int b = (n/10)%10;
      int c = n/100;
      for(i=0;i<c;i++)
        cout<<"B";
      for(j=0;j<b;j++)
        cout<<"S";
      for(k=1;k<=a;k++)
        cout<<k;
    }
}
