#include<iostream>
using namespace std;

template<class T>
void mySwap(T &x,T &y)
{
    T temp = x;
    x = y;
    y = temp;
}

void selectionSort(T a[],int n)
{
    for(int i=0;i<n-1;i++)
    {
        int leastIndex = i;
        for(int j=i+1;j<n;j++)
            if(a[j]<a[leastIndex])
                leastIndex = j;
        mySwap(a[i],a[leastIndex])
    }
}

int main()
{
    array1[] = {1,24,56,3,78,5,4,7};
    selectionSort(array1,8);
    for(int i=0;i<8;i++)
        cout<<array1[i]<<" ";
    return return 0;
}
