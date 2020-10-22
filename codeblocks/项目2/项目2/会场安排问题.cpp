#include<iostream>
using namespace std;
struct huiyi
{
    int x;//开始时间
    int y;//结束时间
    bool z;//活动是否安排过
};
int main()
{
    int n;
    cin>>n;
    huiyi huiyi[n];//n场会议，设已经排好序
    for(int i=0;i<n;i++)
    {
        cin>>huiyi[i].x>>huiyi[i].y;
        huiyi[i].z = false;
    }
    int num=1;//安排了第一场会议
    int cont = 0;
    int en;
    while(num<n)
    {
        cont++;
        for(int i=0;i<n;i++)
            if(huiyi[i].z==false)
            {
                en = huiyi[i].y;
                huiyi[i].z = true;
                num++;
                break;
            }
        for(int i=0;i<n;i++)
        {
            if(huiyi[i].z==false&&huiyi[i].x>=en)
            {
                en = huiyi[i].y;
                huiyi[i].z = true;
                num++;
            }
        }
    }
    cout<<"所需的总会场是"<<cont<<endl;
    return 0;
}
