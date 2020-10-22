#include<stdio.h>
int main()
{
    int a;
    int count1 = 0;
    //printf("输入一个整数:");
    scanf("%d",&a);
    while(a!=1)
    {
        if(a%2==0)
            a = a/2;
        else
            a = (3*a+1)/2;
        count1++;
    }
    printf("%d",count1);
    return 0;
}
