#include<iostream>
using namespace std;
int main()
{
    int n;//
    int m;//
    int s[1000];
    int t[1000];//存储大小
    int tn[1000];//存储个数
    for(int i=0;i<1000;i++)
        tn[i]=0;
    cin>>n;
    for(int i = 0;i < n;i++)
        cin>>s[i];
    t[0] = s[0];
    tn[0] = 1;
    m = 1;
    for(int i = 1;i < n;i++)
    {
        for(int j = 0;j<m;j++)
        {
            if(t[j]==s[i])
            {
                tn[j]++;
                break;
            }
            else if(j==m-1)
            {
                t[m] = s[i];
                m++;
            }
        }
    }
    int max = t[0];int maxn = tn[0];
    for(int i=1;i<m;i++)
    {
        if(tn[i]>maxn)
        {
            max = t[i];
            maxn = tn[i];
        }
        else if(tn[i]==maxn&&t[i]<max)
        {
            max = t[i];
            maxn = tn[i];
        }
    }
    cout<<max;
    return 0;
}
