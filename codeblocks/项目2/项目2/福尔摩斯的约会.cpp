#include<iostream>
#include<string>
using namespace std;
int main()
{
    char mosi1[60];
    char mosi2[60];
    char mosi3[60];
    char mosi4[60];
    cin>>mosi1>>mosi2>>mosi3>>mosi4;
    int i=0;
    while(mosi1[i]&&mosi2[i])
    {
        if(mosi1[i]==mosi2[i]&&mosi1[i]>='A'&&mosi1[i]<='G')
        {
            switch(mosi1[i])
            {
            case 'A':
                cout<<"MON ";
                break;
            case 'B':
                cout<<"TUE ";
                break;
            case 'C':
                cout<<"WED ";
                break;
            case 'D':
                cout<<"THU ";
                break;
            case 'E':
                cout<<"FRI ";
                break;
            case 'F':
                cout<<"SAT ";
                break;
            case 'G':
                cout<<"SUN ";
                break;
            default:
                break;
            }
            break;
        }
        i++;
    }
    i++;
    while(mosi1[i]&&mosi2[i])
    {
            if(mosi1[i]==mosi2[i]&&mosi1[i]>='0'&&mosi1[i]<='9')
            {
                 cout <<"0"<<mosi1[i]-'0'<<":";
                 break;
            }
            if(mosi1[i]==mosi2[i]&&mosi1[i]>='A'&&mosi1[i]<='N')
            {
                    cout<<mosi1[i]-55<<":";
                    break;
            }
            i++;
    }
    int j=0;
    while(mosi1[j]&&mosi1[j])
    {
        if(mosi3[j]==mosi4[j]&&((mosi3[j]>='A'&&mosi3[j]<='Z')||(mosi3[j]>='a'&&mosi3[j]<='z')))
           {
               if(j<10)
                  cout<<"0"<<j;
               else
                cout<<j;
                break;
           }
           j++;
    }
    return 0;
}
