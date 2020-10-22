#include"stdio.h"
#include"string.h"
#include"windows.h"
#include"math.h"
#include"time.h"
int main()
{
    char key[32];
    char ikey[32];
    char id[32];
    srand((unsigned)time(NULL));
    int iid;
    iid = rand()%101+12;
    sprintf(key,"%d",iid*8+123);
    printf("你的机器码是%d\n",iid);
    printf("请输入注册码:");
    gets(ikey);
    if(strcmp(key,ikey)==0)
        MessageBoxA(0,"注册成功","这特写不出来还打王者?",MB_OK);
    else
        MessageBoxA(0,"注册失败","这特写不出来还打王者?",MB_OK);
    return 0;
}
