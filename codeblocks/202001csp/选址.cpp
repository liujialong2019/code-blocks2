#include<iostream>
using namespace std;
int main()
{
    int num;
    cin>>num;
    int site[num][2];
    int sum[num][2] = {0};
    int a=0,b=0,c=0,d=0,e=0;
    for(int i=0;i<num;i++)
        cin>>site[i][0]>>site[i][1];
    for(int i=0;i<num;i++)
    {
        int x = site[i][0],y = site[i][1];
        for(int j=0;j<num;j++)
        {
            if((site[j][0]==x&&site[j][1]==y+1)||(site[j][0]==x&&site[j][1]==y-1)||(site[j][0]==x+1&&site[j][1]==y)||(site[j][0]==x-1&&site[j][1]==y))
                sum[i][0]++;
            if((site[j][0]==x+1&&site[j][1]==y+1)||(site[j][0]==x-1&&site[j][1]==y-1)||(site[j][0]==x+1&&site[j][1]==y-1)||(site[j][0]==x-1&&site[j][1]==y+1))
                sum[i][1]++;
        }
    }
    for(int i=0;i<num;i++)
    {
        if(sum[i][0]==4)
        {
            if(sum[i][1]==0)
                a++;
            else if(sum[i][1]==1)
                b++;
            else if(sum[i][1]==2)
                c++;
            else if(sum[i][1]==3)
                d++;
            else if(sum[i][1]==4)
                e++;
        }
    }
    cout<<a<<endl<<b<<endl<<c<<endl<<d<<endl<<e;
    return 0;
}
