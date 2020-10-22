#include<iostream>
#include<algorithm>
using namespace std;
int main()
{
    int n;
    cin>>n;
    int arr[n];
    int brr[n];
    for(int i=0;i<n;i++)
        cin>>arr[i];
    for(int i=0;i<n;i++)
        brr[i] = arr[i];
    //еепР
    sort(arr,arr+n);
    int num1 = 0;
    int num2 = 0;
    int x;
    for(int i=0;i<n-1;i++)
    {
        x = arr[0]+arr[1]-1;
        num1 = x + num1;
        arr[1] = arr[0]+arr[1];//更新元素个数
        arr[0] = 1111111111;
        sort(arr,arr+n);
        //for(int i=0;i<n;i++)
            //cout<<arr[i]<<" ";
        //cout<<endl;
    }
    sort(brr,brr+n);
    for(int i=n-1;i>0;i--)
    {
        x = brr[n-1]+brr[n-2]-1;
        num2 = x+num2;
        brr[n-2] = brr[n-1]+brr[n-2];//更新元素个数
        brr[n-1] = 0;
        sort(brr,brr+n);
        //for(int i=0;i<n;i++)
            //cout<<brr[i]<<" ";
        //cout<<endl;
    }
    cout<<"次数最少的合并方案"<<num1<<endl;
    cout<<"次数最多的合并方案"<<num2<<endl;
    return 0;
}
