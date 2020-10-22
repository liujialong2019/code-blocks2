#include<iostream>
#include<stdio.h>
using namespace std;
int main()
{
    int m,n;
    cin>>m;
    float arr[2*m];
    for(int i=0;i<2*m;i++)
        cin>>arr[i];
    cin>>n;
    float brr[n*2];
    for(int i=0;i<2*n;i++)
        cin>>brr[i];
    float crr[(m+n)*2];
    int k=0;
    //for(int i=0;i<2*m;i++)
       // cout<<arr[i]<<" ";
       for(int i=0,j=0;i<m*2||j<n*2;)
       {
        if(i<m*2&&j<n*2)
           {
           if(arr[i]==brr[j])
           {
               crr[k]=arr[i];
               i++;
               j++;
               k++;
               crr[k]=arr[i]+brr[j];
               i++;
               j++;
               k++;
           }
           else if(arr[i]>brr[j])
           {
               crr[k]=arr[i];
               i++;
               k++;
               crr[k]=arr[i];
               i++;
               k++;
           }
           else if(arr[i]<brr[j])
           {
               crr[k]=brr[j];
               j++;
               k++;
               crr[k]=brr[j];
               j++;
               k++;
           }
       }
       else if(i>=m*2&&j<n*2)
       {
           crr[k]=brr[j];
           j++;
           k++;
           crr[k]=brr[j];
           j++;
           k++;
       }
       else if(j>=n*2&&i<m*2)
       {
           crr[k]=arr[i];
           i++;
           k++;
           crr[k]=arr[i];
           i++;
           k++;
       }
    }
    cout <<(k+1)/2;
        for(int i=0;i<k;i++)
    {
      if(crr[i+1]!=0)
      {
            cout<<" "<<crr[i];
            printf(" %.1f",crr[++i]);
      }
      else
         i = i + 1;
    }
    return 0;
}
//当算法向后读取数据的过程中有可能有指数相同的数据
