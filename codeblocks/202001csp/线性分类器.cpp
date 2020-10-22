#include<iostream>
using namespace std;
int main()
{
    int n,m;
    //cout<<"start:"<<endl;
    cin>>n>>m;
    int arr1[n][2];
    char arr2[n][1];
    int brr1[m][3];
    for(int i=0;i<n;i++)
        cin>>arr1[i][0]>>arr1[i][1]>>arr2[i][0];
    for(int i=0;i<m;i++)
        cin>>brr1[i][0]>>brr1[i][1]>>brr1[i][2];
    //for(int i=0;i<n;i++)
        //cout<<arr1[i][0]<<" "<<arr1[i][1]<<" "<<arr2[i][0]<<endl;
   // for(int i=0;i<m;i++)
        //cout<<brr1[i][0]<<" "<<brr1[i][1]<<" "<<brr1[i][2]<<endl;
    for(int i=0;i<m;i++)
    {
        int x = brr1[i][1], y = brr1[i][2],z = brr1[i][0];
        int y1,y2;
        char ch;
        int leibie;
        for(int j=0;j<n;j++)
        {
            y1 = z + arr1[j][0]*x;
            y2 = -1*y*arr1[j][1];
            if(y1>y2&&j==0)
            {
                ch = arr2[j][0];
                leibie = 1;
            }
            else if(y1<y2&&j==0)
            {
                leibie = 2;
                ch = arr2[j][0];
            }
            if(leibie==1){
                if(y1>y2)
                {
                    if(arr2[j][0]!=ch)
                        {
                            cout<<"No"<<endl;
                            break;
                        }
                }
                if(y1<y2)
                {
                    if(arr2[j][0]==ch)
                    {
                        cout<<"No"<<endl;
                        break;
                    }
                }
                }
            if(leibie==2){
              if(y1<y2)
                if(arr2[j][0]!=ch)
                {
                    cout<<"No"<<endl;
                    break;
                }
                if(y1>y2)
                    if(arr2[j][0]==ch)
                {
                    cout<<"No"<<endl;
                    break;
                }
                }
           // cout<<leibie<<" "<<ch<<" "<<arr2[j][0]<<" "<<y1<<" "<<y2<<" "<<endl;
            if(j==n-1&&i<m-1)
                cout<<"Yes"<<endl;
            else if(j==n-1&&i==m-1)
                cout<<"Yes";
        }
    }
    return 0;
}
/*
9 3
1 1 A
1 0 A
1 -1 A
2 2 A
2 3 B
0 1 A
3 1 B
1 3 B
2 0 A
0 2 -3
-3 0 2
-3 1 1
*/
