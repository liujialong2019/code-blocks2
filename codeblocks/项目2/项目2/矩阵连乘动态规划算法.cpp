#include<iostream>
#include <iomanip>
using namespace std;
int n = 6;
int main()
{
    int p[7] = {30,35,15,5,10,20,25};//矩阵系数
    //cout<<p[0]<<" "<<p[6]<<endl;
    int m[7][7];//备忘录
    int s[7][7];//记录最优解位置
    for(int i=0;i<7;i++)
        for(int j=0;j<7;j++)
    {
        m[i][j]=0;
        s[i][j]=0;
    }
    void MatrixChain(int p[7],int n,int m[7][7],int s[7][7]);
    MatrixChain(p,n,m,s);
    for(int i=0;i<7;i++)
    {
        for(int j=0;j<7;j++)
            cout<< setw(10)<< m[i][j];
            cout<<endl;
    }
        for(int i=0;i<7;i++)
    {
        for(int j=0;j<7;j++)
            cout<<s[i][j]<<" ";
            cout<<endl;
    }
    return 0;
}
    void MatrixChain(int p[7],int n,int m[7][7],int s[7][7])
    {
        int i,r;
        for(i=1;i<=n;i++)
            m[i][i]=0;//赋值
        for(r=2;r<=n;r++)
            for(int i=1;i<=n-r+1;i++)
        {
            int j = i+r-1;
            m[i][j]=m[i+1][j]+p[i-1]*p[i]*p[j];
            s[i][j]=i;
            for(int k=i+1;k<j;k++)
            {
                int t = m[i][k]+m[k+1][j]+p[i-1]*p[k]*p[j];
                if(t<m[i][j])
                {
                    m[i][j] = t;
                    s[i][j] = k;
                }
            }
        }
    }
