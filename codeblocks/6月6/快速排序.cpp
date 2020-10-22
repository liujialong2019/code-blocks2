#include<iostream>
using namespace std;
int Partition(int a[],int p,int r);
void QuickSort(int a[],int p,int r)
{
    if(p<r){
        int q = Partition(a,p,r);
        QuickSort(a,p,q-1);
        QuickSort(a,q+1,r);
    }
}
int Partition(int a[],int p,int r)
{
    int i=p,j=r+1;
    int x = a[p];
    while(true){
        while(a[i++]<x&&i<r);
        while(a[--j]>x);
        if(i>=j)
            break;
        swap(a[i],a[j]);
    }
    a[p] = a[j];
    a[j] = x;
    return j;
}
int main()
{
    int  a[8] = {1,3,6,7,8,2,5,4};
    QuickSort(a,0,7);
    for(int i=0;i<8;i++)
        cout<<a[i]<<" ";
    return 0;
}
