#include<iostream>
using namespace std;
int main()
{
    int a,b;
    cin>>a>>b;
    int arr[7];
    int i = 0;
    int j = 0;
    int c = a + b;
        if(c<0)
    {
        cout<<"-";
        c = 0 - c;
    }
    if(c==0)
    {
        cout<<"0";
    }
    while(c)
    {
        arr[i]=c%10;
        c=c/10;
        i++;
    }
    int k = i%3;
    int x = i;
    for(i=i-1;i>=0;i--)
    {
        if(j==3||(i==x-k-1&&k!=0))
        {
            cout<<",";
            j=0;
        }
        cout<<arr[i];
        j++;
    }
}

