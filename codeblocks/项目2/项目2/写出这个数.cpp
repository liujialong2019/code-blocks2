#include<iostream>
using namespace std;

int main()
{
    int sum = 0;
    int i = 0,j = 0;
    int temp;
    char array0[100];
    int array1[100];
    cin>>array0;
    //cout<<array0<<endl;
    while(array0[i]!='\0')
    {
        sum = sum + array0[i] - '0';
        i++;
    }
    //cout << sum << endl;
    while(sum!=0)
    {
        temp = sum%10;
        sum = sum/10;
        array1[j] = temp;
        j++;
    }
    for(j=j-1;j>=0;j--)
    {
        switch(array1[j])
        {
        case 1 :
            cout << "yi";
            break;
        case 2:
            cout << "er";
            break;
        case 3:
            cout << "san";
            break;
        case 4:
            cout << "si";
            break;
        case 5:
            cout << "wu";
            break;
        case 6:
            cout << "liu";
            break;
        case 7:
            cout << "qi";
            break;
        case 8:
            cout << "ba";
            break;
        case 9:
            cout << "jiu";
            break;
        case 0:
            cout << "ling";
            break;
        default:
            ;
            }
        if(j>0)
            cout <<" ";
    }
    return 0;
}
