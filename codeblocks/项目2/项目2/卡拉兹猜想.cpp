//排除法
#include<iostream>
using namespace std;
int main()
{
    int n;
    cin>>n;
    int kala[n];
    int paixu[50];
    int i,j=0;
    for(i=0;i<n;i++)
    {
        cin>>kala[i];
    }
    //for(i=0;i<n;i++)
    //{
     //   cout<<kala[i]<<" ";
    //}
    for(i=0;i<n;i++)
    {
        if(kala[i]<0)
            continue;
        else
        {
            int temp = kala[i];
            while(temp!=1)
            {
                if(temp%2==0)
                    temp = temp/2;
                else
                    temp = (3*temp+1)/2;
                for(int j=0;j<n;j++)
                        if(kala[j]==temp)
                        {
                            kala[j] = -1;
                            break;
                        }


            }
        }
    }
    //for(i=0;i<n;i++)
        //cout<<kala[i]<<" ";
    for(i=0;i<n;i++)
    {
        if(kala[i]>0)
        {
            paixu[j] = kala[i];
            j++;
        }
    }
    //for(j=j-1;j>=0;j--)
        //cout <<paixu[j];
    //自定义排序算法，逐个输出
    int m;
    for(i=0;i<j;i++)
    {
            int largest = paixu[i];
            for(int k=0;k<j;k++)
            {
                if(paixu[k]>largest)
                {
                    largest = paixu[k];
                    m = k;
                }
            }

        //注意输出空格，特别是末尾空格
            if(i<j-1)
               cout << largest << " ";
            else
                cout <<largest;
            paixu[m] = -1;

    }
    return 0;
}

