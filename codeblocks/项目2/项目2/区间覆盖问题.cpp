#include<iostream>
#include<algorithm>
using namespace std;
int main()
{
    int n,k;
    int sum = 1;
    cin>>n>>k;
    int arr[n];
    for(int i=0;i<n;i++)
        cin>>arr[i];
    sort(arr,arr+n);
    for(int i=0,temp = arr[0];i<n;i++)
        if(arr[i]-temp>k)
        {
            temp = arr[i];
            sum++;
        }
    cout<<"需要的最大区间数目是"<<sum;
    return 0;
}
