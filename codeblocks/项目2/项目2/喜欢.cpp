#include<iostream>
using namespace std;
int main()
{
    char abc[3];
    cout<<"松子是否喜欢家龙，请根据现实情况输入选项:"<<endl;
    cout<<"A.松子不喜欢家龙;"<<endl;
    cout<<"B.松子敷衍家龙;"<<endl;
    cout<<"C.松子偷偷打游戏不带家龙;"<<endl;
    cout<<"请输入您的选项;"<<endl;
    cin>>abc;
    if(abc[0]=='A'&&abc[1]=='B'&&abc[2]=='C')
        cout<<"回答正确;"<<endl;
    else
    {
        cout<<"回答错误"<<endl;
        cout<<"正确答案是ABC;"<<endl;
    }
    while(1)
    {
    cout<<"修复松子不喜欢家龙的bug中,QAQ;"<<endl;
    cout<<"松子是否喜欢家龙?请输入'Yes'或者'No';"<<endl;
    string ab;
    cin>>ab;
    if(ab=="Yes")
    {
        cout<<"松子已经喜欢家龙,循环终止。"<<endl;
        break;
    }
    else
        cout<<"bug还在修复，请继续答题；"<<endl;
   }
   return 0;
}
