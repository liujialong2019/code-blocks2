#include<iostream>
using namespace std;

int count = 0;//重复元素个数

//template(class Type)
inline void Swap(int &a,int &b)
{
    int temp = a;
    a = b;
    b = temp;
}

//template(class Type)
void Perm(int list[],int k,int m)
{
    if(k==m)
    {
        for(int i=0;i<=m;i++)
            cout<<list[i]<<" ";
        cout<<endl;
    }
    else
    {
        for(int i=k;i<=m;i++)
        {
            count[]
            for(int j=0;j<count;j++)
                if(list[k]==list[j])
                  continue;
            Swap(list[k],list[i]);
            Perm(list,k+1,m);
            Swap(list[k],list[i]);
        }
    }
}

int main()
{
    int arr[5] = {1,2,3,4,5};
    Perm(arr,0,4);
    return 0;
}
