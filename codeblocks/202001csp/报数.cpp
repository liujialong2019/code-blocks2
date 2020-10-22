#include<iostream>
using namespace std;

int main()
{
    int num;
    int count = 1;
    int a=0,b=0,c=0,d=0;
    cin>>num;
    for(int i=0;i<num;i++)
    {
        int yes = 0;
        int x = count;
        if(x%7==0)
            yes = 1;
        else
        {
            while(x!=0)
            {
                int y = x%10;
                x = x/10;
                if(y==7)
                {
                    yes = 1;
                    break;
                }
            }
        }
        if(yes == 1)
        {
            if(count%4==1)
                a++;
            else if(count%4==2)
                b++;
            else if(count%4==3)
                c++;
            else if(count%4==0)
                d++;
            i--;
        }
        count++;
    }
    cout<<a<<endl;
    cout<<b<<endl;
    cout<<c<<endl;
    cout<<d;
    return 0;
}
