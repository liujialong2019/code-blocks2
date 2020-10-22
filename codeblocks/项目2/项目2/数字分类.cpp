#include<iostream>
#include<iomanip>
using namespace std;

int main()
{
    int n;
    int max0;
    int a1=0,a2=0,a3=0,a4=0,a5=0;
    int b1=0,b2=0,b3=0,b4=0,b5=0;
    cin>>n;
    int a[n];
    for(int i=0;i<n;i++)
        cin>>a[i];
    //for(int i=0;i<n;i++)
        //cout<<a[i]<<" ";
    for(int i=0;i<n;i++)
    {
        int j = a[i]%5;
        switch(j)
        {
        case 0:
            if(a[i]%2==0)
            {
                b1=1;
                a1 = a1+a[i];
            }
            break;
        case 1:
            b2++;
            if(b2%2==1)
               a2 = a2 + a[i];
            else
               a2 = a2 - a[i];
            break;
        case 2:
            b3++;
            break;
        case 3:
            b4++;
            a4 = a4+a[i];
            break;
        case 4:
            b5++;
            if(b5==1)
                max0=a[i];
            else if(max0<a[i])
                max0=a[i];
            break;
        default:
            ;

        }
        }
    if(b1>0)
        cout<<a1;
    else
        cout<<"N";
    if(b2>0)
        cout<<" "<<a2;
    else
        cout<<" N";
    if(b3>0)
        cout<<" "<<b3;
    else
        cout<<" N";
    if(b4>0)
    {
         double x;
         x = a4/(b4*1.0);
         cout<<" "<<fixed<<setprecision(1)<<x;
    }
    else
        cout<<" N";
    if(b5>0)
        cout<<" "<<max0;
    else
        cout<<" N";
    return 0;
}
