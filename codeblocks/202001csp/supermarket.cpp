#include<iostream>
using namespace std;
int happy(int L,int R,int a,int b,int c)
{
    int x = -2*a/b;
    if(a=0)
    {
        if(b>=0)
            return b*R+c;
        else
            return b*L+c;
    }
    else if(a<0)
    {
        if(x>=R)
            return a*R*R+b*R+c;
        else if(L>x)
            return a*L*L+b*L+c;
        else
            return a*x*x+b*x+c;
    }
    else
    {
        if(L>x)
            return a*R*R+b*R+c;
        else if(x>R)
            return a*L*L+b*L+c;
        else
            return (a*R*R+b*R+c)>(a*L*L+b*L+c)?(a*R*R+b*R+c):(a*L*L+b*L+c);
    }
}
int main()
{
    long long sum = 0;
    ios::sync_with_stdio(false);
    int m,n;
    cin>>m>>n;
    int shop[n][5];
    for(int i=0;i<n;i++)
        cin>>shop[i][0]>>shop[i][1]>>shop[i][2]>>shop[i][3]>>shop[i][4];
    int relat[m][3];
    for(int i=0;i<n;i++)
        cin>>relat[i][0]>>relat[i][1]>>relat[i][2];
    for(int i=0;i<n;i++)
        sum = sum + happy(shop[i][0],shop[i][1],shop[i][2],shop[i][3],shop[i][4]);
    cout<<sum;
    return 0;
}
