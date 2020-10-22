#include <iostream>
#include<fstream>//文件输出输入流的库
#include<vector>//使用vector数组，解决数据个数不确定的问题
#include <algorithm>//使用这个库中的sort函数，简化代码
using namespace std;
int main()
{
    fstream a, b;//定义两个数据流
    a.open("a.txt", ios::in);//读取打开文件,注意是ios::in
    vector<double> data;//定义一个vector数组，储存数据
    double x;
    while (a >> x)//从a文件中读取数据
    {
        data.push_back(x);//在vector数组中增加成员
    }
    sort(data.begin(), data.end());//从小到大排序
    b.open("b.txt", ios::out);//输入（写）打开文件，注意是ios::out
    if (b)
    {
        for (int i=0;i<data.size(); i++)//注意data.size后面要加（）,表示data数组共有多少个成员
        {
            b << data[i] << " ";//一个一个将数据输出到b
        }
    }
    a.close();//一定要关闭文件！！！
    b.close();//一定要关闭文件！！！
    return 0;
}

