#include<iostream>
using namespace std;
int main()
{
    int num;//子序列个数
    int b[3];//单次划分存储
    int c[3];//总的划分数存储
    int d[100][3];
    int d1 = 0;//测试数据总个例
    while(1)//直到K=0
    {
        int k=0;
        //cout<<endl<<"输入元素个数:";
        cin>>num;
        if(num==0)
            break;//输入元素个数为零时候结束
        int a[num];//存储输入的元素个数
        for(int i=0;i<num;i++)
            cin>>a[i];
        for(int i=0;i<num;i++)
            if(a[i]<0)
               k++;
        if(k==num)//所有元素都为负数
        {
            b[0]=0;
            b[1]=a[0];
            b[2]=a[num-1];
        }
        else
        {
            b[0] = a[0];
            b[1] = a[0];
            b[2] = a[0];
        }
        //求最大子序列和
        for(int i=1;i<=num;i++)
        {
            int max=0;
            for(int i1=0;i1<i;i1++)
                max = max + a[i1];
            for(int j=0;j<num-i+1;j++)
            {
                int sum = 0;
                int k1 = 0;
                for(k1=0;k1<i;k1++)
                    sum = sum + a[j+k1];
                if(sum>max)
                {
                    max = sum;
                    b[0] = sum;
                    b[1] = a[j];
                    b[2] = a[j+k1-1];
                }
            }
            if(i==1)
            {
                 c[0] = b[0];
                 c[1] = b[1];
                 c[2] = b[2];
            }
            else if(b[0]>c[0])
            {
                 c[0] = b[0];
                 c[1] = b[1];
                 c[2] = b[2];
            }
            if(b[0]==c[0]&&b[1]<c[1])
            {
                 c[0] = b[0];
                 c[1] = b[1];
                 c[2] = b[2];
            }
        }
        for(int i=0;i<3;i++)
        {
            d[d1][0] = c[0];
            d[d1][1] = c[1];
            d[d1][2] = c[2];
        }
        d1++;
     }
     for(int i=0;i<d1;i++)
     {
         for(int j=0;j<3;j++)
           cout<<d[i][j]<<" ";
         cout<<endl;
     }
}
