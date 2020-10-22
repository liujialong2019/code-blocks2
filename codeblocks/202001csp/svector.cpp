#include<iostream>
using namespace std;
int main()
{
    //cout<<"start:"<<endl;
    int n,a,b;//数量
    int x,y;//存索引
    long long sum = 0;
    cin>>n>>a>>b;
    //int array[n] = {0};//存值
    int *array = new int[n];
    //int array1[a];//存索引
    int *array1 = new int[a];
    //int  brray[n] = {0};//存值
    int *brray = new int[n];
    //int  brray1[b];//存索引
    int *brray1 = new int[b];
    for(int i=0;i<n;i++)
    {
        array[i] = 0;
        brray[i] = 0;
    }
    for(int i=0;i<a;i++)
    {
        cin>>x;
        array1[i] = x - 1;
        cin>>array[x - 1];
    }
    for(int i=0;i<b;i++)
    {
        cin>>y;
        brray1[i] = y - 1;
        cin>>brray[y - 1];
    }
    /*for(int i = 0;i<a;i++)
        cout<<array1[i]<<" ";
    cout<<endl;
    for(int i = 0;i<b;i++)
        cout<<brray1[i]<<" ";
    cout<<endl;*/
    for(int i=0,j=0;i<a&&j<b;)
    {
       if(array1[i]>brray1[j])
       {
           //cout<<"array1[i] = "<<array1[i]<<" "<<"brray1[j] = "<<brray1[j]<<" ";
           j++;
       }
       else if(array1[i]<brray1[j])
       {
           //cout<<"array1[i] = "<<array1[i]<<" "<<"brray1[j] = "<<brray1[j]<<" ";
            i++;
       }
       else
       {
           //cout<<"array1[i] = "<<array1[i]<<" "<<"brray1[j] = "<<brray1[j]<<" ";
           sum = sum + array[array1[i++]]*brray[brray1[j++]];
       }
        //cout<<endl;
    }
    cout<<sum;
    delete array1;
    delete array;
    delete brray1;
    delete brray;
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
