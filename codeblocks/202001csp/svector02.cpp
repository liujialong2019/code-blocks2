#include<iostream>
using namespace std;
int main()
{
    //cout<<"start:"<<endl;
    int n,a,b;//数量
    int x,y;//存索引
    long long sum = 0;
    cin>>n>>a>>b;
    int array[n] = {0};//存值
    int array1[a];
    int brray[n] = {0};//存值
    for(int i=0;i<a;i++)
    {
        cin>>x;
        array1[i] = x - 1;
        cin>>array[x - 1];
    }
    for(int i=0;i<b;i++)
    {
        cin>>y;
        cin>>brray[y - 1];
    }
    for(int i=0;i<a;i++)
    {
        sum = sum + array[array1[i]]*brray[array1[i]];
    }
    cout<<sum;
    return 0;
}
/*
10 3 4
4 5
7 -3
10 1
1 10
4 20
5 30
7 40
*/
