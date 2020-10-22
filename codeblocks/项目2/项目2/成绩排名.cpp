#include<iostream>
using namespace std;
int main()
{
    int n;
    cin>>n;
    char name[n][11];
    char sno[n][11];
    int grade[n];
    for(int i=0;i<n;i++)
    {
        cin>>name[i]>>sno[i]>>grade[i];
    }
    //for(int i=0;i<n;i++)
    //{
    //    cout <<name[i]<<" "<<sno[i]<<" "<<grade[i]<<endl;
    //}
    int grademax = grade[0];
    int grademin = grade[0];
    int count1 = 0,count2 = 0;
    for(int i=0;i<n;i++)
    {
        if(grade[i]>grademax)
        {
            grademax = grade[i];
            count1 = i;
        }
        if(grade[i]<grademin)
        {
            grademin = grade[i];
            count2 = i;
        }
    }
    cout << name[count1] <<" "<<sno[count1]<<endl;
    cout << name[count2] <<" "<<sno[count2];
    return 0;
}
