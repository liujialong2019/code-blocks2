#include<iostream>
#include<cmath>
using namespace std;
int main()
{
    int m,n;
    cin>>m>>n;
    int i=0;
    int j=2;
    int k=0;
    bool issushu(int n);
    for(i=0;i<n;j++)
    {
        if(issushu(j))
        {
            i++;
        }
        if(i>=m&&issushu(j))
        {
            k++;
            if(i==n||k==10)
               cout<<j;
            else
               cout <<j<<" ";
            if(k==10)
            {
                cout<<endl;
                k=0;
            }
        }
    }
}

bool issushu(int n)
{
    int k = sqrt(n);
    int i = 2;
    for(i=2;i<=k;i++)
    {
        if(n%i==0)
            return false;
    }
    if(i>k)
        return true;
}
