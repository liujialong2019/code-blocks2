#include <windows.h>
#include <time.h>
#include <iostream>
#include <string>
using namespace std;
int map[41][41];
int arr[20];
int brr[40];
int arr1[20];
int brr1[40];
int expect;
int expect1;
void Frame();
void PrintMap();
void HideCursor();
void GoToxy(int x,int y);//光标移动函数
int level = 1;
string words[100] = {"覃子倩","刘家龙","你是我的宝呀","子倩是人间理想","一起听歌吧",
"山河远阔，人间烟火","哈哈哈哈","嘻嘻嘻嘻","我好馋倩倩","把倩倩装进口袋","我要听你娇喘","今晚那个吗",
"倩倩是我的小仙女","爱你一万年","动感懵逼","等等倩倩的一个皮筋","嘤嘤嘤","555  555","给倩倩多一点关心",
"给倩倩多一点陪伴","子倩","已加入一起听歌","噗嗤","妹妹","哥哥","八岐鬼切","保安、早","心悦与子倩",
"倩倩不要生家龙的气啦","哼哼哼","倩倩不想起床","对你没有免疫力","哥哥你好会哦","妹妹也很棒呢","打电话嘛","要抱抱",
"妹妹在我身下","从前喜欢一个人","现在喜欢一个人","一定把子倩娶回家睡","芙蓉帐暖","等风也等你","哒哒哒","宝贝",
"干得漂亮","大佬救命","保护我方倩倩","不让你受别人伤害","好好学习","钟情于你","往后余生","和你恋爱未来可期",
"憨憨","你的名字","月光宝盒之大圣娶亲","想和你散步","想和你一起躺着","想和你牵手","假如我年少有为不自卑","声音甜甜的",
"粘人哦","喜欢你","爱你哟","呜呜呜","幸运字符","你是我的宝贝","我宝贝你","噗哈哈哈哈","害羞","你醒了记得找我","人家超想哭的嘛",
"宝贝记得吃早饭","好好睡","和你一起很舒服","我喜欢覃子倩","我家小仙女","鸭鸭不知所措","小脸通红橙黄绿青蓝紫","妹妹我想",
"想入非非","亲亲倩倩","把妹妹床上压","不良倩倩","呸","你想干嘛","要抱抱","拍怕我","拍拍你","这样这样那样那样","我已经捂住眼睛了",
"你可以亲亲我了","我裂开来","我炸裂了","倩倩是软妹","~~","QQ","想趴哥哥身上","LOVE","比心","陪在我身边"};
int length[100];
int main()
{
    system("mode con cols=88 lines=44");
    HideCursor();
    Frame();
    for(int i = 0;i<100;i++)
        length[i] = words[i].size();
    PrintMap();
    while(1)
    {
        //GetMap();
    };
    return 0;
}
void ColorChoose(int color)
{
    switch(color)
    {
    case 5://粉红色
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_BLUE|FOREGROUND_RED);
        break;
    }
}
void Frame()//打印游戏框架
{
    ColorChoose(5);
    cout<<"  ▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁  ";
    cout<<endl;
    for(int i=0;i<39;i++)
    {
       cout<<"▕                                                                              ▏"<<endl;
    }
    cout<<"  ▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔  ";
}
void PrintMap()//打印地图多了背景颜色
{

    for(int i=1;i<40;i++)
    {
        for(int i1=0;i1<20;i1++)
            arr[i1] = rand()%39+1;
        for(int i1=0;i1<40;i1++)
            brr[i1] = rand()%100;
        for(int j=1;j<40;j++)
        {
            for(int k=0;k<20;k++)
            {
                GoToxy(1*2,arr[k]);
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_RED);//背景黑色
                cout<<"                                                                              ";
                GoToxy(2*j,arr[k]);
                ColorChoose(5);
                if(41-j>length[brr[k]]/2)
                    cout<<words[brr[k]];
                else
                    {
                        for(int k1=0;k1<41-j;k1=k1+2)
                        cout<<words[brr[k]][k1]<<words[brr[k]][k1+1];
                    }
                if(j==39)
                {
                    GoToxy(39*2,arr[k]);
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_RED);//背景黑色
                    cout<<"  ";
                }
            }
            Sleep(200);
        }
            if(i==39)
                i=1;
    }
}
void GoToxy(int x,int y)
{
    COORD coord;
    coord.X=x;
    coord.Y=y;
    HANDLE  str=GetStdHandle(STD_OUTPUT_HANDLE);//获得标准输出句柄
    SetConsoleCursorPosition(str,coord);//
}
void HideCursor()//隐藏光标
{
    CONSOLE_CURSOR_INFO cursor_info={1,0};
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE),&cursor_info);
}
/*
void PrintMap()//打印地图多了背景颜色
{
    for(int i=1;i<40;i)
    {
        expect = rand()%100;
        for(int j=1;j<41;j++)
            //if(map[i][j]!=4)
        {
            /*GoToxy(1*2,i);
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_RED);//背景黑色
            cout<<"                                                                              ";
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|BACKGROUND_RED|FOREGROUND_BLUE);
            GoToxy(2*j,i);
            if(41-j>length[expect]/2)
                cout<<words[expect];
            else
            {
                for(int k=0;k<41-j;k=k+2)
                    cout<<words[expect][k]<<words[expect][k+1];
            }
            Sleep(200);
            if(j==41)
                j=1;
        }
            GoToxy(39*2,i);
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_RED);//背景黑色
            cout<<"  ";
            Sleep(200);
    }
}*/
/*循环一行代码
    for(int i=1;i<40;i++)
    {
        expect = rand()%100;
        for(int j=1;j<40;j++)
            //if(map[i][j]!=4)
        {
            GoToxy(1*2,i);
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_RED);//背景黑色
            cout<<"                                                                              ";
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|BACKGROUND_RED|FOREGROUND_BLUE);
            GoToxy(2*j,i);
            if(41-j>length[expect]/2)
                cout<<words[expect];
            else
            {
                for(int k=0;k<41-j;k=k+2)
                    cout<<words[expect][k]<<words[expect][k+1];
            }
            Sleep(200);
        }
            GoToxy(39*2,i);
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_RED);//背景黑色
            cout<<"  ";
            Sleep(200);
    }
*/
/*25行失败
    for(int i=0;i<25;i++)
    {
        expect = rand()%100;//字幕
        expect1 = rand()%39;

        for(int j=1;i<41;j++)
            if(map[expect1][j]!=4)
        {
            GoToxy(1+2,expect1);
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_RED);//背景黑色
            cout<<"                                                                              ";
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|BACKGROUND_RED|FOREGROUND_BLUE);
            GoToxy(2*j,expect1);
            if(41-j>length[expect]/2)
                cout<<words[expect];
            else
                {
                    for(int k=0;k<41-j;k=k+2)
                         cout<<words[expect][k]<<words[expect][k+1];
                }
        }
        GoToxy(39*2,expect1);
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_RED);//背景黑色
        cout<<"  ";
        Sleep(200);
    }*/

/*    /*
        for(int j=1;j<41;j++)
        {
                if(map[expect1][j]!=4)
                {
                    GoToxy(1*2,expect1);
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_RED);//背景黑色
                    cout<<"                                                                              ";
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|BACKGROUND_RED|FOREGROUND_BLUE);
                    GoToxy(2*j,expect1);
                    if(41-j>length[expect1]/2)
                        cout<<words[expect];
                    else
                    {
                        for(k=0;k<41-j;k=k+2)
                            cout<<words[expect][k]<<words[expect][k+1];
                    }
                }
            if(j==41)
            {
                j=1;
            GoToxy(39*2,k+expect1);
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_RED);//背景黑色
            cout<<"  ";
        }
        */
/*多字幕
void PrintMap()//打印地图多了背景颜色
{

    for(int i=1;i<40;i++)
    {
        for(int i1=0;i1<20;i1++)
            arr[i1] = rand()%39+1;
        for(int i1=0;i1<20;i1++)
            arr1[i1] = rand()%20+1;
        for(int i1=0;i1<40;i1++)
            brr[i1] = rand()%100;
        for(int i1=0;i1<40;i1++)
            brr1[i1] = rand()%100;
        expect = rand()%100;
        for(int j=1;j<40;j++)
            //if(map[i][j]!=4)
        {
            for(int k=0;k<20;k++)
            {
                j = arr1[k];
                //i = 40 - arr[k];
                GoToxy(1*2,arr[k]);
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_RED);//背景黑色
                cout<<"                                                                              ";
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|BACKGROUND_RED|FOREGROUND_BLUE);
                GoToxy(2*j,arr[k]);
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_RED);//背景黑色
                for(int i = 0;i<arr1[k];i++)
                    cout<<" ";
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|BACKGROUND_RED|FOREGROUND_BLUE);
                //GoToxy(2*j,arr[k]);
                if(41-j>length[brr[k]]/2)
                    cout<<words[brr[k]];
                else
                    {
                        for(int k1=0;k1<41-j;k1=k1+2)
                        cout<<words[brr[k]][k1]<<words[brr[k]][k1+1];
                    }
                if(j==39)
                {
                    GoToxy(39*2,arr[k]);
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_RED);//背景黑色
                    cout<<"  ";
                }
            }
            Sleep(200);
        }
            if(i==39)
                i=1;
    }
}*/
