#include<stdio.h>
int len;//输入长度
int sum;//和
int *data;//数据
char *output;
void GetInput()// 获取输入
{
    int i;
    printf("输入集合元素个数: ");
    scanf("%d", &len);
    data = new int[len];
    output = new char[len];
    for(i = 0; i < len; i++)
        {
            printf("输入第%d个数: ", i+1);
            scanf("%d", &data[i]);
            output[i] = 'N';
        }
    printf("输入所求的和: ");
    scanf("%d", &sum);
    int GetRes()//回溯法
    {
        int p = 0;//指向当前值
        int temp = 0;//当前子集合和
        while(p >= 0)
            {
        if('N' == output[p])
            { // 选中当前项
                output[p] = 'Y';
                temp += data[p];
             if(temp == sum)
                return 1;
            if(temp>sum)
                {
                    output[p] = 'N';
                    temp -= data[p];
                }
             p++;
           }
       if(p>=len)
        {//开始回朔
           while('Y' == output[p-1])
            {
                p--;
                output[p] = 'N';
                temp -= data[p];
                if(p < 1)
                    return 0;
            }
           while('N' == output[p-1])
            {
                p--;
                if(p < 1)
                    return 0;
            }
            output[p-1] = 'N';
            temp -= data[p-1];
        }
        }
        return 0;
        }// 打印结果.
void PrintRes()
    {
        int i;
        printf("\r\n所求子集为: ");
        for(i = 0; i < len; i++)
            if('Y' == output[i])
            printf("%d ", data[i]);
    }
int main()
{
    GetInput();
    if(GetRes())
        PrintRes();
    else
        printf("无解！");
    return 0;
}
