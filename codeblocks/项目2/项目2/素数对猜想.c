#include<stdio.h>
#include<math.h>
int main()
{
    int n;
    int count=0;//计数器
    scanf("%d",&n);
    int issushu(int m);//素数判断函数
    for(int i=2;i<=n-2;i++)//从（1，n）,易知（1，3）不是素数对，但是素数判断函数会计数
                           //所以从2开始计数，排除影响（如果我没猜错，测试点2的数据是n=3；
    {
        if(issushu(i)==1&&issushu(i+2)==1)
            count++;
    }
    printf("%d",count);
}
//素数判断函数
int issushu(int m)
{
    int i;
    int sqrt1 = sqrt(m);
    for(i=2;i<=sqrt1;i++)
    {
        if(m%i==0)
            return 0;
    }
    if(i+1>sqrt1&&m%i!=0)
        return 1;
    else
        return 0;
}
